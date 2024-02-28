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
}