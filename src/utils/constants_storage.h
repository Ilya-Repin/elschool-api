#pragma once

#include <string_view>

namespace constants {

  using namespace std::literals;

  struct Url {
    static constexpr std::string_view  url_logon = "https://elschool.ru/logon/index"sv;
    static constexpr std::string_view  url_privateoffice = "https://elschool.ru/privateoffice"sv;
    static constexpr std::string_view url_diaries = "https://elschool.ru/users/diaries"sv;
    static constexpr std::string_view url_marks_without_headers = "https://elschool.ru/users/diaries/grades"sv;
  };

  struct tokens {
    static constexpr uint64_t two_days_in_seconds = 172800;
  };
}