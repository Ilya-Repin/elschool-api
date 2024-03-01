#include "users_handler.hpp"
#include "../../utils/exceptions.h"
#include "userver/clients/http/component.hpp"
#include "userver/components/component_context.hpp"

namespace {

void CheckArgument(const std::string& arg, const std::string& arg_name) {
  if (arg.empty()) {
    throw std::invalid_argument("No '" + arg_name + "' argument!");
  }
}

}  // namespace

namespace users_handler {

UsersHandler::UsersHandler(const components::ComponentConfig& config,
                           const components::ComponentContext& context)
    : HttpHandlerBase(config, context),
      user_manager_(context.FindComponent<user_manager::UserManager>()) {}

std::string UsersHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext&) const {
  if (request.GetMethod() == server::http::HttpMethod::kPost) {
    return HandlePostRequest(request);
  } else if (request.GetMethod() == server::http::HttpMethod::kDelete) {
    return HandleDeleteRequest(request);
  } else if (request.GetMethod() == server::http::HttpMethod::kPut) {
    return HandlePutRequest(request);
  }
}

std::string UsersHandler::HandlePostRequest(const userver::server::http::HttpRequest& request) const {
  const std::string& login = request.GetArg("login");
  const std::string& password = request.GetArg("password");

  std::optional<std::string> id;
  try {
    CheckArgument(login, "login");
    CheckArgument(password, "password");
    id = user_manager_.AddUserData(login, password);
  }catch (const std::invalid_argument& e) {
    throw server::handlers::ClientError(
        server::handlers::ExternalBody{e.what()});
  } catch (const exceptions::UserException &e) {
    throw server::handlers::InternalServerError(
        server::handlers::ExternalBody{e.what()});
  }

  if (id) {
    request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
    return *id;
  } else {
    throw server::handlers::InternalServerError(
        server::handlers::ExternalBody{"Failed to add user!"s});
  }
}

std::string UsersHandler::HandleDeleteRequest(const userver::server::http::HttpRequest& request) const {
  const std::string& id = request.GetArg("id");
  bool res;
  try {
    CheckArgument(id, "id");

    res = user_manager_.DeleteUserData(id);
  } catch (const std::invalid_argument& e) {
    request.SetResponseStatus(userver::server::http::HttpStatus::kBadRequest);
    throw server::handlers::ClientError(
        server::handlers::ExternalBody{e.what()});
  }

  if (res) {
    request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
    return "Deleted!"s;
  } else {
    request.SetResponseStatus(
        userver::server::http::HttpStatus::kInternalServerError);
    throw server::handlers::ClientError(server::handlers::ExternalBody{
        "Failed to delete user with id - "s + id});
  }
}

std::string UsersHandler::HandlePutRequest(const userver::server::http::HttpRequest& request) const {
  const std::string& id = request.GetArg("id");
  const std::string& login = request.GetArg("login");
  const std::string& password = request.GetArg("password");

  bool res;

  try {
    CheckArgument(id, "id");
    CheckArgument(login, "login");
    CheckArgument(password, "password");

    res = user_manager_.UpdateUserData(id, login, password);
  } catch (const std::invalid_argument& e) {
    request.SetResponseStatus(userver::server::http::HttpStatus::kBadRequest);
    throw server::handlers::ClientError(
        server::handlers::ExternalBody{e.what()});
  } catch (const exceptions::UserException &e) {
    request.SetResponseStatus(userver::server::http::HttpStatus::kInternalServerError);
    throw server::handlers::ClientError(
        server::handlers::ExternalBody{e.what()});
  }

  if (res) {
    request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
    return "Updated!"s;
  } else {
    request.SetResponseStatus(
        userver::server::http::HttpStatus::kInternalServerError);
    throw server::handlers::ClientError(server::handlers::ExternalBody{
        "Failed to update user with id - "s + id});
  }
}

void AppendUsersHandler(userver::components::ComponentList& component_list) {
  component_list.Append<UsersHandler>();
}

}  // namespace users_handler