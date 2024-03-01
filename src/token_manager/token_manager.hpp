#pragma once

#include <unordered_map>
#include "userver/clients/http/client.hpp"
#include "userver/clients/http/component.hpp"
#include "userver/components/component_list.hpp"
#include "userver/storages/postgres/cluster.hpp"
#include "userver/storages/postgres/component.hpp"
#include "userver/utils/assert.hpp"

#include "../utils/constants_storage.h"
#include "token_cache.hpp"

namespace token_manager {

enum TokenGroupOption { ALL, OLD };

using namespace userver;

class TokenManager : public components::LoggableComponentBase {
 public:
  static constexpr std::string_view kName = "token-manager";

  TokenManager(const components::ComponentConfig& config,
               const components::ComponentContext& context);
  ~TokenManager() = default;

  std::size_t InvalidateTokenGroup(TokenGroupOption option);
  void Invalidate(const boost::uuids::uuid &uuid);
  std::string GetToken(const std::string& id);

  static userver::yaml_config::Schema GetStaticConfigSchema();

 private:
  bool CheckToken(std::string token);

  std::string elschool_url_;
  TokenCache& token_cache_;
  clients::http::Client& http_client_;
  storages::postgres::ClusterPtr pg_cluster_;
};

void AppendTokenManager(userver::components::ComponentList& component_list);

}  // namespace token_manager
