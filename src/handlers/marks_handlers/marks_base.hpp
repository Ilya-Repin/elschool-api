#pragma once

#include <string>
#include <unordered_map>
#include <userver/clients/http/client.hpp>

#include "utils/constants_storage.h"

namespace marks_base {

using namespace std::literals;

class MarksBase {
 protected:
  std::string GetUrlHeaders(userver::clients::http::Client& http_client, std::string token, std::string elschool_url) const;
};

}  // namespace base_marks