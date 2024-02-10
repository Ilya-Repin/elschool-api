#include "userver/clients/http/component.hpp"
#include "userver/components/component_context.hpp"

#include "../../../utils/exceptions.h"
#include "average_marks.hpp"

namespace average_marks {

AverageMarks::AverageMarks(const components::ComponentConfig& config,
                           const components::ComponentContext& context)
    : HttpHandlerBase(config, context),
      http_client_{context.FindComponent<userver::components::HttpClient>()
                       .GetHttpClient()},
      token_manager_(context.FindComponent<token_manager::TokenManager>()),
      parser_(parser::Strategy::AVERAGE_MARKS) {}

std::string AverageMarks::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext& context) const {
  const std::string& id = request.GetArg("id");

  if (id.empty()) {
    request.SetResponseStatus(userver::server::http::HttpStatus::kBadRequest);
    throw server::handlers::ClientError(
        server::handlers::ExternalBody{"No 'id' argument"s});
  }

  std::string JWToken;
  try {
    JWToken = token_manager_.GetToken(id);
  } catch (exceptions::TokenException& e) {
    request.SetResponseStatus(
        userver::server::http::HttpStatus::kInternalServerError);
    throw server::handlers::ClientError(server::handlers::ExternalBody{e.what()});
  }
  std::string headers = GetUrlHeaders(http_client_, JWToken);

  std::string url =
      std::string(constants::Url::url_marks_without_headers) + headers;

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
      request.SetResponseStatus(
          userver::server::http::HttpStatus::kInternalServerError);

      throw server::handlers::ClientError(
          server::handlers::ExternalBody{e.what()});
    }
  } else {
    request.SetResponseStatus(
        userver::server::http::HttpStatus::kInternalServerError);
    throw server::handlers::ClientError(
        server::handlers::ExternalBody{"Error during mark's request"s});
  }

  formats::json::ValueBuilder builder;

  for (auto& i : marks) {
    builder[i.first] = i.second;
  }

  request.SetResponseStatus(userver::server::http::HttpStatus::kOk);

  return ToString(builder.ExtractValue());
}

void AppendAverageMarks(userver::components::ComponentList& component_list) {
  component_list.Append<AverageMarks>();
}

}  // namespace average_marks