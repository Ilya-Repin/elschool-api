#include "token_handler.hpp"

namespace token_handler {

TokenHandler::TokenHandler(const userver::components::ComponentConfig& config,
                           const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
      token_manager_(context.FindComponent<token_manager::TokenManager>()) {}


std::string TokenHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext&) const {
  const std::string& invalidate = request.GetArg(constants::Args::option);

  token_manager::TokenGroupOption option;

  if (invalidate == constants::Args::all) {
    option = token_manager::TokenGroupOption::ALL;
  } else if (invalidate == constants::Args::old) {
    option = token_manager::TokenGroupOption::OLD;
  }

  std::size_t amount = token_manager_.InvalidateTokenGroup(option);

  std::string response = fmt::format("Invalidated {} tokens"s, amount);

  return response;
}

void AppendTokenHandler(userver::components::ComponentList& component_list) {
  component_list.Append<TokenHandler>();
}

}  // namespace token_handler