#pragma once

#include "../../user_manager/user_manager.hpp"
#include "../../utils/constants_storage.h"
#include "userver/clients/http/client.hpp"
#include "userver/clients/http/component.hpp"
#include "userver/components/component_list.hpp"
#include "userver/components/minimal_server_component_list.hpp"
#include "userver/server/handlers/http_handler_base.hpp"

namespace users_handler {

using namespace userver;
using namespace std::literals;

class UsersHandler final : public server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-users"sv;

  using HttpHandlerBase::HttpHandlerBase;

  UsersHandler(const components::ComponentConfig& config,
               const components::ComponentContext& context);

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext& context) const override;

 private:
  std::string HandlePostRequest(const userver::server::http::HttpRequest &request) const;
  std::string HandlePutRequest(const userver::server::http::HttpRequest &request) const;
  std::string HandleDeleteRequest(const userver::server::http::HttpRequest &request) const;

  user_manager::UserManager& user_manager_;
};

void AppendUsersHandler(userver::components::ComponentList& component_list);

}  // namespace service_template