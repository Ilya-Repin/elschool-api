#include "token_manager.hpp"

namespace token_manager {

using namespace std::literals;

TokenManager::TokenManager(const components::ComponentConfig& config,
                           const components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      token_cache_(TokenCache::GetInstance()),
      http_client_{context.FindComponent<userver::components::HttpClient>()
                       .GetHttpClient()},
      pg_cluster_(context
                      .FindComponent<userver::components::Postgres>(
                          "postgres-elschool-db")
                      .GetCluster()),
      elschool_url_(config[constants::Args::elschool_url].As<std::string>()) {
  token_cache_.SetInvalidationTime(config[constants::Args::invalidation_time].As<int>());
}

std::size_t TokenManager::InvalidateTokenGroup(TokenGroupOption option) {
  std::size_t amount = 0;

  if (option == TokenGroupOption::ALL) {
    amount = token_cache_.InvalidateAllTokens();
  } else if (option == TokenGroupOption::OLD) {
    amount = token_cache_.InvalidateOldTokens();
  }

  return amount;
}

void TokenManager::Invalidate(const boost::uuids::uuid& uuid) {
  token_cache_.InvalidateToken(uuid);
}

bool TokenManager::CheckToken(std::string token) {
  std::unordered_map<std::string, std::string> cookies;
  cookies[constants::Args::JWToken.data()] = token;

  auto response = http_client_.CreateRequest()
                      .follow_redirects(false)
                      .get(elschool_url_ + std::string(constants::Paths::path_privateoffice))
                      .cookies(cookies)
                      .timeout(std::chrono::seconds{15})
                      .perform();

  return response->IsOk() &&
         response->status_code() == clients::http::Status::OK;
}

std::string TokenManager::GetToken(const std::string& id) {
  boost::uuids::uuid uuid;

  try {
    boost::uuids::string_generator gen;
    uuid = gen(id);
  } catch (std::exception& e) {
    throw std::invalid_argument("Received id is not a uuid!"s);
  }

  if (!token_cache_.IsInvalidatingOldTokens()) {
    std::optional<std::string> found = token_cache_.FindToken(uuid);
    if (found) {
      bool result = CheckToken(*found);

      if (result) {
        return *found;
      } else {
        token_cache_.InvalidateToken(uuid);
      }
    }
  }

  LOG_INFO() << "There's no actual token in cache with uuid: " << id;

  std::string token;

  std::string login, password;

  auto result = pg_cluster_->Execute(
      userver::storages::postgres::ClusterHostType::kMaster,
      "SELECT login, password FROM elschool_api_schema.elschool_users WHERE id = $1"s,
      uuid);

  if (!result.IsEmpty()) {
    struct Data {
      std::string login, password;
    };

    auto user_info =
        result.AsSingleRow<Data>(userver::storages::postgres::kRowTag);

    login = user_info.login;
    password = user_info.password;

  } else {
    throw exceptions::TokenException("No user in database with uuid - "s + id);
  }

  std::string data = fmt::format("login={}&password={}&GoogleAuthCode="s, login, password);

  auto response = http_client_.CreateRequest()
                      .follow_redirects(false)
                      .post(elschool_url_ + std::string(constants::Paths::path_logon))
                      .data(data)
                      .headers({
                          {userver::http::headers::kContentLength,
                           std::to_string(data.length())},
                      })
                      .timeout(std::chrono::seconds{15})
                      .perform();

  if (response->cookies().empty()) {
    throw exceptions::TokenException("Can't get cookie for user with uuid - "s +
                                     id);
  }

  std::unordered_map<std::string, std::string> cookies;

  auto cookie_map = response->cookies();
  token = cookie_map.at(constants::Args::JWToken.data()).Value();

  if (token.empty()) {
    throw exceptions::TokenException(
        "Got empty token from elschool for user with uuid - "s + id);
  }

  if (!token_cache_.IsInvalidatingOldTokens()) {
    token_cache_.AddToken(uuid, token);
  }

  return token;
}

userver::yaml_config::Schema TokenManager::GetStaticConfigSchema() {
  return userver::yaml_config::MergeSchemas<userver::components::LoggableComponentBase>(
      R"(
type: object
description: token manager
additionalProperties: false
properties:
    elschool_url:
        type: string
        description: url of elschool
    invalidation_time:
        type: integer
        description: lifetime of token in seconds (must be less than a week)
)");
}

void AppendTokenManager(userver::components::ComponentList& component_list) {
  component_list.Append<TokenManager>();
  component_list.Append<userver::components::Postgres>("postgres-elschool-db");
  component_list.Append<userver::clients::dns::Component>();
}

}  // namespace token_manager