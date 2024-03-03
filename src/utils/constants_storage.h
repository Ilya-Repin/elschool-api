#pragma once

#include <string_view>

namespace constants {

  using namespace std::literals;

  struct Paths {
    static constexpr std::string_view path_logon = "/logon/index"sv;
    static constexpr std::string_view path_privateoffice = "/privateoffice"sv;
    static constexpr std::string_view path_diaries = "/users/diaries"sv;
    static constexpr std::string_view path_marks = "/users/diaries/grades"sv;
  };

  struct tokens {
    static constexpr uint64_t two_days_in_seconds = 172800;
  };

  struct Args {
    static constexpr std::string_view elschool_url = "elschool_url"sv;
    static constexpr std::string_view id = "id"sv;
    static constexpr std::string_view JWToken = "JWToken"sv;
    static constexpr std::string_view option = "option"sv;
    static constexpr std::string_view all = "all"sv;
    static constexpr std::string_view old = "old"sv;
    static constexpr std::string_view login = "login"sv;
    static constexpr std::string_view password = "password"sv;
    static constexpr std::string_view invalidation_time = "invalidation_time"sv;
  };
}  // namespace constants