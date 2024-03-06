#include "marks_base.hpp"

namespace marks_base {

std::string MarksBase::GetUrlHeaders(userver::clients::http::Client& http_client, std::string token, std::string elschool_url) const {
  std::unordered_map<std::string, std::string> cookies;
  cookies[constants::Args::JWToken.data()] = token;

  auto response = http_client.CreateRequest()
                      .follow_redirects(false)
                      .get(elschool_url + std::string(constants::Paths::path_diaries))
                      .cookies(cookies)
                      .timeout(std::chrono::seconds{15})
                      .perform();

  std::string body = response->body();

  auto user_headers = std::string(body.substr(
      body.find("?"),
      body.find("here") - body.find("?") - 2));  // добавить std::string::npos

  const auto to_delete = "amp;"s;
  size_t start{user_headers.find(to_delete)};

  while (start != std::string::npos) {
    user_headers.erase(start, to_delete.length());
    start = user_headers.find(to_delete, start + to_delete.length());
  }

  return user_headers;
}

}  // namespace marks_base