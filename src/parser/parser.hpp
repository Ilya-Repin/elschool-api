#pragma once

#include <gumbo.h>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace parser {

enum Strategy { AVERAGE_MARKS, TODAY_MARKS };

struct MarkupElem {
  std::string tag;
  std::string attr_class;
};

class TimeProvider {
 public:
  virtual int GetMonth() = 0;
  virtual int GetSemester() = 0;
  virtual int GetTrimester() = 0;
  virtual int GetQuarter() = 0;
  virtual std::string GetDate() = 0;
};

class CurrentTimeProvider : public TimeProvider {
 public:
  int GetMonth();
  int GetSemester();
  int GetTrimester();
  int GetQuarter();
  std::string GetDate();
};

class ParsingStrategy {
 public:
  virtual void Parse(std::string html, std::unordered_map<std::string, std::string> &) = 0;

  virtual ~ParsingStrategy() = default;
};

class AverageParsingStrategy : public ParsingStrategy {
 public:
  void Parse(std::string html, std::unordered_map<std::string, std::string> &average_marks);
  AverageParsingStrategy(TimeProvider& time_provider);
  ~AverageParsingStrategy() = default;

 private:
  void FindAverageMarks(GumboNode *table, std::unordered_map<std::string, std::string> &);

  TimeProvider& time_provider_;
};

class TodayParsingStrategy : public ParsingStrategy {
 public:
  void Parse(std::string html, std::unordered_map<std::string, std::string> &today_marks);
  TodayParsingStrategy(TimeProvider& time_provider);
  ~TodayParsingStrategy() = default;

 private:
  void FindTodayMarks(GumboNode *table, std::unordered_map<std::string, std::string> &);
  void GetPeriodsMarks(GumboNode *tag_marks, std::string &marks);

  TimeProvider& time_provider_;
};

class Parser {
 public:
  std::unordered_map<std::string, std::string> Parse(std::string html) const;

  Parser(Strategy parsing_strategy);
  Parser(Strategy parsing_strategy, TimeProvider& time_provider);
  ~Parser() = default;

 private:
  std::unique_ptr<ParsingStrategy> strategy_;
  CurrentTimeProvider time_provider_; // Стандартное время
};

}  // namespace parser