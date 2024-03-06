#include "users_handler.hpp"

namespace {

void CheckArgument(const std::string& arg, const std::string_view& arg_name) {
  if (arg.empty()) {
    throw std::invalid_argument(fmt::format("No '{}' argument!", arg_name));
  }
}

}

namespace users_handler {

UsersHandler::UsersHandler(const userver::components::ComponentConfig& config,
                           const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
      user_manager_(context.FindComponent<user_manager::UserManager>()) {}

std::string UsersHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext&) const {
  if (request.GetMethod() == userver::server::http::HttpMethod::kPost) {
    return HandlePostRequest(request);
  }
  if (request.GetMethod() == userver::server::http::HttpMethod::kDelete) {
    return HandleDeleteRequest(request);
  }
  if (request.GetMethod() == userver::server::http::HttpMethod::kPut) {
    return HandlePutRequest(request);
  }

  request.SetResponseStatus(
      userver::server::http::HttpStatus::kMethodNotAllowed);
  return "Unsupported http method!"s;
}

std::string UsersHandler::HandlePostRequest(
    const userver::server::http::HttpRequest& request) const {
  const std::string& login = request.GetArg(constants::Args::login);
  const std::string& password = request.GetArg(constants::Args::password);

  std::optional<std::string> id;
  try {
    CheckArgument(login, constants::Args::login);
    CheckArgument(password, constants::Args::password);
    id = user_manager_.AddUserData(login, password);
  } catch (const std::invalid_argument& e) {
    throw userver::server::handlers::ClientError(
        userver::server::handlers::ExternalBody{e.what()});
  } catch (const exceptions::UserException& e) {
    throw userver::server::handlers::InternalServerError(
        userver::server::handlers::ExternalBody{e.what()});
  }

  if (id) {
    request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
    return *id;
  }

  throw userver::server::handlers::InternalServerError(
      userver::server::handlers::ExternalBody{"Failed to add user!"s});
}

std::string UsersHandler::HandleDeleteRequest(
    const userver::server::http::HttpRequest& request) const {
  const std::string& id = request.GetArg("id");
  bool res;

  try {
    CheckArgument(id, "id");

    res = user_manager_.DeleteUserData(id);
  } catch (const std::invalid_argument& e) {
    request.SetResponseStatus(userver::server::http::HttpStatus::kBadRequest);
    throw userver::server::handlers::ClientError(
        userver::server::handlers::ExternalBody{e.what()});
  }

  if (res) {
    request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
    return "Deleted!"s;
  }

  request.SetResponseStatus(
      userver::server::http::HttpStatus::kInternalServerError);

  throw userver::server::handlers::ClientError(
      userver::server::handlers::ExternalBody{
          "Failed to delete user with id - "s + id});
}

std::string UsersHandler::HandlePutRequest(
    const userver::server::http::HttpRequest& request) const {
  const std::string& id = request.GetArg(constants::Args::id);
  const std::string& login = request.GetArg(constants::Args::login);
  const std::string& password = request.GetArg(constants::Args::password);

  bool res;

  try {
    CheckArgument(id, constants::Args::id);
    CheckArgument(login, constants::Args::login);
    CheckArgument(password, constants::Args::password);

    res = user_manager_.UpdateUserData(id, login, password);
  } catch (const std::invalid_argument& e) {
    request.SetResponseStatus(userver::server::http::HttpStatus::kBadRequest);
    throw userver::server::handlers::ClientError(
        userver::server::handlers::ExternalBody{e.what()});
  } catch (const exceptions::UserException& e) {
    request.SetResponseStatus(
        userver::server::http::HttpStatus::kInternalServerError);
    throw userver::server::handlers::ClientError(
        userver::server::handlers::ExternalBody{e.what()});
  }

  if (res) {
    request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
    return "Updated!"s;
  }

  request.SetResponseStatus(
      userver::server::http::HttpStatus::kInternalServerError);
  throw userver::server::handlers::ClientError(
      userver::server::handlers::ExternalBody{
          "Failed to update user with id - "s + id});
}

void AppendUsersHandler(userver::components::ComponentList& component_list) {
  component_list.Append<UsersHandler>();
}

}  // namespace users_handler