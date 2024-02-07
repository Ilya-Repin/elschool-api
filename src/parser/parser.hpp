#pragma once

#include <gumbo.h>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

namespace parser {

enum Strategy { AVERAGE_MARKS, TODAY_MARKS };

struct MarkupElem {
  std::string tag;
  std::string attr_class;
};

class ParsingStrategy {
 public:
  virtual void Parse(std::string html, std::unordered_map<std::string, std::string> &) = 0;
};

class AverageParsingStrategy : public ParsingStrategy {
 public:
  void Parse(std::string html, std::unordered_map<std::string, std::string> &average_marks);

 private:
  void FindAverageMarks(GumboNode *table, std::unordered_map<std::string, std::string> &);
};

class TodayParsingStrategy : public ParsingStrategy {
 public:
  void Parse(std::string html, std::unordered_map<std::string, std::string> &today_marks);

 private:
  void FindTodayMarks(GumboNode *table, std::unordered_map<std::string, std::string> &);
  void GetPeriodsMarks(GumboNode *tag_marks, std::string &marks);

};

class Parser {
 public:
  std::unordered_map<std::string, std::string> Parse(std::string html,
      Strategy parsing_strategy) const;
};

}  // namespace parser