#include "token_handler.hpp"
#include "userver/clients/http/component.hpp"
#include "userver/components/component_context.hpp"

namespace token_handler {

TokenHandler::TokenHandler(const components::ComponentConfig& config,
                           const components::ComponentContext& context)
    : HttpHandlerBase(config, context),
      token_manager_(context.FindComponent<token_manager::TokenManager>()) {}

std::string TokenHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext& context) const {
  const std::string& invalidate = request.GetArg("option");

  token_manager::TokenGroupOption option;

  std::size_t amount = 0;

  if (invalidate == "all"s) {
    amount = token_manager_.InvalidateTokenGroup(
        token_manager::TokenGroupOption::ALL);
  } else if (invalidate == "old"s) {
    amount = token_manager_.InvalidateTokenGroup(
        token_manager::TokenGroupOption::OLD);
  }

  std::string response = "Invalidated "s + std::to_string(amount) + " tokens"s;

  return response;
}

void AppendTokenHandler(userver::components::ComponentList& component_list) {
  component_list.Append<TokenHandler>();
}

}  // namespace token_handler