#include "user_manager.hpp"

namespace {

using namespace userver;

const storages::postgres::Query kSelectUserData{
    "SELECT id FROM elschool_api_schema.elschool_users WHERE "
    "login=$1::varchar(100) AND password=$2::varchar(100)",
    storages::postgres::Query::Name{"select_user_data"}};

const storages::postgres::Query kInsertUserData{
    "INSERT INTO elschool_api_schema.elschool_users VALUES($1, $2, $3)",
    storages::postgres::Query::Name{"insert_user_data"}};

const storages::postgres::Query kUpdateUserData{
    "UPDATE elschool_api_schema.elschool_users SET login=$2, password=$3 WHERE "
    "id=$1",
    storages::postgres::Query::Name{"update_user_data"}};

const storages::postgres::Query kDeleteUserData{
    "DELETE FROM elschool_api_schema.elschool_users WHERE id=$1",
    storages::postgres::Query::Name{"delete_user_data"}};
}

namespace user_manager {

using namespace std::literals;

UserManager::UserManager(const components::ComponentConfig& config,
                         const components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      token_manager_(context.FindComponent<token_manager::TokenManager>()),
      http_client_{context.FindComponent<userver::components::HttpClient>()
                       .GetHttpClient()},
      pg_cluster_(context
                      .FindComponent<userver::components::Postgres>(
                          "postgres-elschool-db")
                      .GetCluster()),
      elschool_url_(config[constants::Args::elschool_url].As<std::string>()) {}

std::optional<std::string> UserManager::AddUserData(const std::string &login,
                                                    const std::string &password) {


  if (CheckUserData(login, password)) {
    boost::uuids::uuid uuid;

    storages::postgres::ResultSet result_select =
        pg_cluster_->Execute(storages::postgres::ClusterHostType::kSlave,
                             kSelectUserData, login.c_str(), password.c_str());

    if (result_select.IsEmpty()) {
      boost::uuids::random_generator gen;
      uuid = gen();

      auto result_insert =
          pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                               kInsertUserData, uuid, login, password);

      if (!result_insert.RowsAffected()) {
        return std::nullopt;
      }

    } else {
      uuid = result_select.AsSingleRow<boost::uuids::uuid>();
    }

    const std::string id = boost::uuids::to_string(uuid);

    return id;
  }

  return std::nullopt;
}

bool UserManager::UpdateUserData(const std::string &id, const std::string &new_login,
                                 const std::string &new_password) {
  boost::uuids::uuid uuid;

  try {
    boost::uuids::string_generator gen;
    uuid = gen(id);
  } catch(std::exception& e) {
    throw std::invalid_argument("Received id is not a uuid!"s);
  }

  if (!CheckUserData(new_login, new_password)) {
    throw std::invalid_argument("Invalid new login and password!"s);
  }

  auto result = pg_cluster_->Execute(storages::postgres::ClusterHostType::kMaster,
                                  kUpdateUserData, uuid, new_login, new_password);

  if (result.RowsAffected()) {
    token_manager_.Invalidate(uuid);
    return true;
  }

  return false;
}

bool UserManager::DeleteUserData(const std::string &id) {
  boost::uuids::uuid uuid;

  try {
    boost::uuids::string_generator gen;
    uuid = gen(id);
  } catch(std::exception& e) {
    throw std::invalid_argument("Received id is not a uuid!"s);
  }

  auto result_delete = pg_cluster_->Execute(
      storages::postgres::ClusterHostType::kMaster, kDeleteUserData, uuid);

  if (result_delete.RowsAffected()) {
    token_manager_.Invalidate(uuid);

    return true;
  }

  return false;
}

bool UserManager::CheckUserData(const std::string &login, const std::string &password) const {
  const std::string data = fmt::format("login={}&password={}&GoogleAuthCode="s, login, password);

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

  if (response->status_code() == 302) {
    return (response->body().find("privateoffice"s) != std::string::npos);
  }

  throw exceptions::UserException("Error during checking user data!");
}

userver::yaml_config::Schema UserManager::GetStaticConfigSchema() {
  return userver::yaml_config::MergeSchemas<userver::components::LoggableComponentBase>(
      R"(
type: object
description: user manager
additionalProperties: false
properties:
    elschool_url:
        type: string
        description: url of elschool
)");
}

void AppendUserManager(userver::components::ComponentList& component_list) {
  component_list.Append<UserManager>();
}

}  // namespace user_manager