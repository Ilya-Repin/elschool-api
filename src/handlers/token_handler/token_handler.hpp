#pragma once

#include "../../token_manager/token_manager.hpp"
#include "../../utils/constants_storage.h"
#include "userver/clients/http/client.hpp"
#include "userver/clients/http/component.hpp"
#include "userver/components/component_list.hpp"
#include "userver/components/minimal_server_component_list.hpp"
#include "userver/server/handlers/http_handler_base.hpp"

namespace token_handler {

using namespace userver;
using namespace std::literals;

class TokenHandler final : public server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-invalidate-token"sv;

  using HttpHandlerBase::HttpHandlerBase;

  TokenHandler(const components::ComponentConfig& config,
               const components::ComponentContext& context);

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext& context) const override;

 private:
  token_manager::TokenManager& token_manager_;
};

void AppendTokenHandler(userver::components::ComponentList& component_list);

}  // namespace token_handler