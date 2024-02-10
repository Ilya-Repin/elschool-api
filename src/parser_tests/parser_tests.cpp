#include <fstream>
#include "userver/utest/utest.hpp"
#include "../parser/parser.hpp"
#include "mocked_time_provider.hpp"
#include "test_constants.h"

UTEST(ParserTestSuite, TodayMarksNoLessons) {
  using namespace std::literals;

  MockedTimeProvider time_provider;
  time_provider.SetDate("11.11.2022"s);

  parser::Parser parser(parser::Strategy::TODAY_MARKS, time_provider);
  std::unordered_map<std::string, std::string> result = parser.Parse(test_constants::html);

  UASSERT(result.empty());
}

UTEST(ParserTestSuite, TodayMarksOneLesson) {
  using namespace std::literals;

  MockedTimeProvider time_provider;
  time_provider.SetDate("28.10.2022"s);

  parser::Parser parser(parser::Strategy::TODAY_MARKS, time_provider);
  std::unordered_map<std::string, std::string> result = parser.Parse(test_constants::html);

  UASSERT(!result.empty());
  UASSERT(result.size() == 1);
  UASSERT(result.at("Эльфийский язык как государственный язык Лесного Королевства"s).length() == 2);
  UASSERT(result.at("Эльфийский язык как государственный язык Лесного Королевства"s) == "22"s);

  result.clear();


  time_provider.SetDate("26.04.2023"s);
  result = parser.Parse(test_constants::html);

  UASSERT(!result.empty());
  UASSERT(result.size() == 1);
  UASSERT(result.at("Эльфийский язык как государственный язык Лесного Королевства"s).length() == 7);
  UASSERT(result.at("Эльфийский язык как государственный язык Лесного Королевства"s) == "4444555"s);

  result.clear();

  time_provider.SetDate("15.10.2022"s);
  result = parser.Parse(test_constants::html);

  UASSERT(!result.empty());
  UASSERT(result.size() == 1);
  UASSERT(result.at("Алхимия"s).length() == 4);
  UASSERT(result.at("Алхимия"s) == "3345"s);

  result.clear();
}

UTEST(ParserTestSuite, TodayMarksTwoLessons) {
  using namespace std::literals;

  MockedTimeProvider time_provider;
  time_provider.SetDate("31.10.2022"s);

  parser::Parser parser(parser::Strategy::TODAY_MARKS, time_provider);
  std::unordered_map<std::string, std::string> result = parser.Parse(test_constants::html);

  UASSERT(!result.empty());
  UASSERT(result.size() == 2);
  UASSERT(result.at("Эльфийский язык как государственный язык Лесного Королевства"s).length() == 1);
  UASSERT(result.at("Эльфийский язык как государственный язык Лесного Королевства"s) == "3"s);
  UASSERT(result.at("Алхимия"s).length() == 2);
  UASSERT(result.at("Алхимия"s) == "23"s);

  result.clear();


  time_provider.SetDate("27.10.2022"s);
  result = parser.Parse(test_constants::html);

  UASSERT(!result.empty());
  UASSERT(result.size() == 2);
  UASSERT(result.at("Алхимия"s).length() == 1);
  UASSERT(result.at("Алхимия"s) == "2"s);
  UASSERT(result.at("Дезинформатика"s).length() == 2);
  UASSERT(result.at("Дезинформатика"s) == "55"s);

}

UTEST(ParserTestSuite, AverageMarksQuarters) {
  using namespace std::literals;

  MockedTimeProvider time_provider;

  time_provider.SetMonth(9);

  parser::Parser parser(parser::Strategy::AVERAGE_MARKS, time_provider);
  std::unordered_map<std::string, std::string> result = parser.Parse(test_constants::html);

  UASSERT(!result.empty());
  UASSERT(result.size() == 3);
  UASSERT(result.at("Эльфийский язык как государственный язык Лесного Королевства"s) == "2"s);
  UASSERT(result.at("Алхимия"s) == "3,33"s);
  UASSERT(result.at("Дезинформатика"s) == "4,92"s);

  result.clear();

  time_provider.SetMonth(11);
  result = parser.Parse(test_constants::html);

  UASSERT(!result.empty());
  UASSERT(result.size() == 3);
  UASSERT(result.at("Эльфийский язык как государственный язык Лесного Королевства"s) == "3"s);
  UASSERT(result.at("Алхимия"s) == "4,2"s);
  UASSERT(result.at("Дезинформатика"s) == "4,82"s);

  result.clear();

  time_provider.SetMonth(3);
  result = parser.Parse(test_constants::html);

  UASSERT(!result.empty());
  UASSERT(result.size() == 3);
  UASSERT(result.at("Эльфийский язык как государственный язык Лесного Королевства"s) == "4"s);
  UASSERT(result.at("Алхимия"s) == "5"s);
  UASSERT(result.at("Дезинформатика"s) == "4,92"s);

  result.clear();


  time_provider.SetMonth(5);
  result = parser.Parse(test_constants::html);

  UASSERT(!result.empty());
  UASSERT(result.size() == 3);
  UASSERT(result.at("Эльфийский язык как государственный язык Лесного Королевства"s) == "5"s);
  UASSERT(result.at("Алхимия"s) == "2,71"s);
  UASSERT(result.at("Дезинформатика"s) == "5"s);

  result.clear();

  time_provider.SetMonth(8);
  result = parser.Parse(test_constants::html);

  UASSERT(result.empty());

  result.clear();
}