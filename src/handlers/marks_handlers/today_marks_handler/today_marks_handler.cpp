#include "today_marks_handler.hpp"

namespace today_marks_handler {

TodayMarksHandler::TodayMarksHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
      token_manager_(context.FindComponent<token_manager::TokenManager>()),
      http_client_{context.FindComponent<userver::components::HttpClient>()
                       .GetHttpClient()},
      parser_(parser::Strategy::TODAY_MARKS),
      elschool_url_(config[constants::Args::elschool_url].As<std::string>()) {}

// TODO Вынести логику из хэндлера

std::string TodayMarksHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext&) const {
  const std::string& uuid = request.GetArg(constants::Args::id);

  if (uuid.empty()) {
    throw userver::server::handlers::ClientError(
        userver::server::handlers::ExternalBody{"No 'id' argument"s});
  }

  std::string JWToken;
  try {
    JWToken = token_manager_.GetToken(uuid);
  } catch (exceptions::TokenException& e) {
    throw userver::server::handlers::InternalServerError(
        userver::server::handlers::ExternalBody{e.what()});
  } catch (std::invalid_argument& e) {
    throw userver::server::handlers::ClientError(
        userver::server::handlers::ExternalBody{e.what()});
  }

  const std::string headers =
      GetUrlHeaders(http_client_, JWToken, elschool_url_);

  const std::string url =
      elschool_url_ + std::string(constants::Paths::path_marks) + headers;

  std::unordered_map<std::string, std::string> cookies;
  cookies[constants::Args::JWToken.data()] = JWToken;

  auto response = http_client_.CreateRequest()
                      .follow_redirects(false)
                      .get(url)
                      .cookies(cookies)
                      .timeout(std::chrono::seconds{15})
                      .perform();

  std::unordered_map<std::string, std::string> marks;

  if (response->IsOk()) {
    try {
      marks = parser_.Parse(response->body());
    } catch (exceptions::ParsingException& e) {
      throw userver::server::handlers::InternalServerError(
          userver::server::handlers::ExternalBody{e.what()});
    }
  } else {
    throw userver::server::handlers::InternalServerError(
        userver::server::handlers::ExternalBody{
            "Error during mark's request"s});
  }

  userver::formats::json::ValueBuilder builder;

  for (auto& mark : marks) {
    builder[mark.first] = mark.second;
  }

  request.SetResponseStatus(userver::server::http::HttpStatus::kOk);

  return ToString(builder.ExtractValue());
}

void AppendTodayMarksHandler(
    userver::components::ComponentList& component_list) {
  component_list.Append<TodayMarksHandler>();
}

userver::yaml_config::Schema TodayMarksHandler::GetStaticConfigSchema() {
  return userver::yaml_config::MergeSchemas<
      userver::server::handlers::HttpHandlerBase>(
      R"(
type: object
description: today marks handler
additionalProperties: false
properties:
    elschool_url:
        type: string
        description: url of elschool
)");
}

}  // namespace today_marks_handler