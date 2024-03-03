#pragma once

#include <userver/clients/http/client.hpp>
#include <userver/clients/http/component.hpp>
#include <userver/components/component_list.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/assert.hpp>
#include <userver/components/component_context.hpp>
#include <userver/http/common_headers.hpp>
#include <userver/utils/uuid4.hpp>
#include <userver/yaml_config/merge_schemas.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "token_manager/token_manager.hpp"
#include "utils/constants_storage.h"
#include "utils/exceptions.h"

namespace user_manager {

using namespace userver;

class UserManager : public components::LoggableComponentBase {
 public:
  static constexpr std::string_view kName = "user-manager";

  UserManager(const components::ComponentConfig& config,
              const components::ComponentContext& context);
  ~UserManager() = default;

  std::optional<std::string> AddUserData(std::string login, std::string password);
  bool UpdateUserData(std::string id, std::string new_login, std::string new_password);
  bool DeleteUserData(std::string id);

  static userver::yaml_config::Schema GetStaticConfigSchema();

 private:
  bool CheckUserData(std::string login, std::string password) const;

  token_manager::TokenManager& token_manager_;
  clients::http::Client& http_client_;
  storages::postgres::ClusterPtr pg_cluster_;
  const std::string elschool_url_;
};

void AppendUserManager(userver::components::ComponentList& component_list);

}  // namespace user_manager
