#include "marks_base.hpp"
#include "../../utils/constants_storage.h"

namespace marks_base {

std::string MarksBase::GetUrlHeaders(userver::clients::http::Client& http_client, std::string token) const {
  std::unordered_map<std::string, std::string> cookies;
  cookies["JWToken"s] = token;
  auto response = http_client.CreateRequest()
                      .follow_redirects(false)
                      .get(std::string(constants::Url::url_diaries))
                      .cookies(cookies)
                      .timeout(std::chrono::seconds{15})
                      .perform();

  std::string body = response->body();

  std::string user_headers = std::string(body.substr(
      body.find("?"),
      body.find("here") - body.find("?") - 2));  // добавить std::string::npos

  std::string to_delete = "amp;"s;
  size_t start{user_headers.find(to_delete)};

  while (start != std::string::npos) {
    user_headers.erase(start, to_delete.length());
    start = user_headers.find(to_delete, start + to_delete.length());
  }

  return user_headers;
}

}