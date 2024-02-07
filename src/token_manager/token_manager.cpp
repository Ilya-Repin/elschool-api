#include "token_manager.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "../utils/exceptions.h"
#include "userver/clients/dns/component.hpp"
#include "userver/components/component_context.hpp"
#include "userver/http/common_headers.hpp"

namespace token_manager {

using namespace std::literals;

TokenManager::TokenManager(const components::ComponentConfig& config,
                           const components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      http_client_{context.FindComponent<userver::components::HttpClient>()
                       .GetHttpClient()},
      pg_cluster_(context
                      .FindComponent<userver::components::Postgres>(
                          "postgres-elschool-db")
                      .GetCluster()),
      token_cache_(TokenCache::GetInstance()) {
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

void TokenManager::Invalidate(const boost::uuids::uuid &uuid) {
  token_cache_.InvalidateToken(uuid);
}

bool TokenManager::CheckToken(std::string token)  {
  std::unordered_map<std::string, std::string> cookies;
  cookies["JWToken"s] = token;

  auto response = http_client_.CreateRequest()
                      .follow_redirects(false)
                      .get(std::string(constants::Url::url_privateoffice))
                      .cookies(cookies)
                      .timeout(std::chrono::seconds{15})
                      .perform();

  return response->IsOk() &&
         response->status_code() == clients::http::Status::OK;
}

std::string TokenManager::GetToken(const std::string &id) {
  boost::uuids::uuid uuid;

  try {
    boost::uuids::string_generator gen;
    uuid = gen(id);
  } catch(std::exception& e) {
    throw std::invalid_argument("Received id is not a uuid!"s);
  }


  std::optional<std::string> found = token_cache_.FindToken(uuid);
  if (found) {
    bool result = CheckToken(*found);

    if (result) {
      return *found;
    } else {
      token_cache_.InvalidateToken(uuid);
    }
  }

  LOG_INFO() << "There's no actual token in cache with uuid: " << id;

  std::string token;

  std::string login, password;

  auto result = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster,
                       "SELECT login, password FROM elschool_api_schema.elschool_users WHERE id = $1"s, uuid);

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

  std::string data =
      "login="s + login + "&password="s + password + "&GoogleAuthCode="s;

  auto response = http_client_.CreateRequest()
                      .follow_redirects(false)
                      .post(std::string(constants::Url::url_logon))
                      .data(data)
                      .headers({
                          {userver::http::headers::kContentLength,
                           std::to_string(data.length())},
                      })
                      .timeout(std::chrono::seconds{15})
                      .perform();

  if (response->cookies().empty()) {
    throw exceptions::TokenException("Can't get cookie for user with uuid - "s + id);
  }

  std::unordered_map<std::string, std::string> cookies;

  auto cookie_map = response->cookies();
  token = cookie_map.at("JWToken"s).Value();

  if (token.empty()) {
    throw exceptions::TokenException("Got empty token from elschool for user with uuid - "s + id);
  }

  token_cache_.AddToken(uuid, token);

  return token;
}

void AppendTokenManager(userver::components::ComponentList& component_list) {
  component_list.Append<TokenManager>();
  component_list.Append<userver::components::Postgres>("postgres-elschool-db");
  component_list.Append<userver::clients::dns::Component>();
}

}  // namespace token_manager