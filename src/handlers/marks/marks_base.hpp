#pragma once

#include <string>
#include <unordered_map>
#include "userver/clients/http/client.hpp"

namespace marks_base {

using namespace std::literals;

class MarksBase {
 protected:
  std::string GetUrlHeaders(userver::clients::http::Client& http_client, std::string token, std::string elschool_url) const;
};

}