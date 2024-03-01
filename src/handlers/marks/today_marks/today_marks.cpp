#include "today_marks.hpp"
#include "../../../utils/exceptions.h"
#include "userver/clients/http/component.hpp"
#include "userver/components/component_context.hpp"
#include "userver/yaml_config/merge_schemas.hpp"

namespace today_marks {

TodayMarks::TodayMarks(const components::ComponentConfig& config,
                       const components::ComponentContext& context)
    : HttpHandlerBase(config, context),
      http_client_{context.FindComponent<userver::components::HttpClient>()
                       .GetHttpClient()},
      token_manager_(context.FindComponent<token_manager::TokenManager>()),
      elschool_url_(config["elschool_url"].As<std::string>()),
      parser_(parser::Strategy::TODAY_MARKS) {}

std::string TodayMarks::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext& context) const {
  const std::string& uuid = request.GetArg("id");

  if (uuid.empty()) {
    throw server::handlers::ClientError(
        server::handlers::ExternalBody{"No 'id' argument"s});
  }

  std::string JWToken;
  try {
    JWToken = token_manager_.GetToken(uuid);
  } catch (exceptions::TokenException& e) {
    throw server::handlers::InternalServerError(
        server::handlers::ExternalBody{e.what()});
  } catch (std::invalid_argument& e) {
    throw server::handlers::ClientError(
        server::handlers::ExternalBody{e.what()});
  }

  std::string headers = GetUrlHeaders(http_client_, JWToken, elschool_url_);

  std::string url =
      elschool_url_ + std::string(constants::Paths::path_marks) + headers;

  std::unordered_map<std::string, std::string> cookies;
  cookies["JWToken"s] = JWToken;

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
      throw server::handlers::InternalServerError(
          server::handlers::ExternalBody{e.what()});
    }
  } else {
    throw server::handlers::InternalServerError(
        server::handlers::ExternalBody{"Error during mark's request"s});
  }

  formats::json::ValueBuilder builder;

  for (auto& i : marks) {
    builder[i.first] = i.second;
  }

  request.SetResponseStatus(userver::server::http::HttpStatus::kOk);

  return ToString(builder.ExtractValue());
}

void AppendTodayMarks(userver::components::ComponentList& component_list) {
  component_list.Append<TodayMarks>();
}

userver::yaml_config::Schema TodayMarks::GetStaticConfigSchema() {
  return userver::yaml_config::MergeSchemas<server::handlers::HttpHandlerBase>(
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

}  // namespace today_marks