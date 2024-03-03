#include "parser.hpp"

// TODO Переписать парсинг

namespace {

GumboNode* FindTag(GumboNode* node, std::stack<parser::MarkupElem>& path) {
  if (path.empty()) {
    return node;
  }

  GumboVector* children = &node->v.element.children;

  for (std::size_t i = 0; i < children->length; ++i) {
    GumboNode* result = static_cast<GumboNode*>(children->data[i]);

    if (strcmp(gumbo_normalized_tagname(result->v.element.tag),
               path.top().tag.c_str()) == 0) {
      if (path.top().attr_class.empty() ||
          strcmp(gumbo_get_attribute(&result->v.element.attributes, "class")
                     ->value,
                 path.top().attr_class.c_str()) == 0) {
        path.pop();

        return FindTag(result, path);
      }
    }
  }

  throw exceptions::ParsingException("Can't find element!");
}

int CountPeriods(GumboNode* tbody) {
  static int periods = 0;

  if (periods > 0) {
    return periods;
  }

  GumboVector* children = &tbody->v.element.children;

  for (std::size_t i = 0; i < children->length; ++i) {
    if (static_cast<GumboNode*>(children->data[i])->v.element.tag ==
        GUMBO_TAG_TR) {
      periods++;
    }
  }

  return periods;
}

}

namespace parser {

using namespace std::literals;

int CurrentTimeProvider::GetMonth() {
  auto now = std::chrono::system_clock::now();

  time_t time = std::chrono::system_clock::to_time_t(now);
  tm* localTime = std::localtime(&time);

  return localTime->tm_mon + 1;
}

int CurrentTimeProvider::GetSemester() {
  int month = GetMonth();
  if (month >= 1 && month <= 6) {
    return 1;
  } else if (month >= 9 && month <= 12) {
    return 2;
  } else {
    return 0;
  }
}


int CurrentTimeProvider::GetTrimester() {
  int month = GetMonth();
  if (month >= 9 && month <= 11) {
    return 1;
  } else if (month == 12 || month == 1 || month == 2) {
    return 2;
  } else if (month >= 3 && month <= 5) {
    return 3;
  } else {
    return 0;
  }
}


int CurrentTimeProvider::GetQuarter() {
  int month = GetMonth();
  if (month >= 9 && month <= 10) {
    return 1;
  } else if (month >= 11 && month <= 12) {
    return 2;
  } else if (month >= 1 && month <= 3) {
    return 3;
  } else if (month >= 3 && month <= 5) {
    return 4;
  } else {
    return 0;
  }
}

std::string CurrentTimeProvider::GetDate() {
  std::time_t currentTime = std::time(nullptr);

  std::tm* localTime = std::localtime(&currentTime);

  std::stringstream ss;
  ss << std::put_time(localTime, "%d.%m.%Y");
  return ss.str();
}

void AverageParsingStrategy::FindAverageMarks(
    GumboNode* table,
    std::unordered_map<std::string, std::string>& average_marks) {
  GumboVector* children = &table->v.element.children;
  std::size_t children_length = children->length;

  std::string first, second;

  for (std::size_t i = 0; i < children_length; ++i) {
    GumboNode* child = static_cast<GumboNode*>(children->data[i]);

    if (child->v.element.tag == GUMBO_TAG_THEAD) {
      GumboNode* tr =
          static_cast<GumboNode*>(child->v.element.children.data[1]);

      GumboNode* th = static_cast<GumboNode*>(tr->v.element.children.data[1]);

      GumboNode* text = static_cast<GumboNode*>(th->v.element.children.data[0]);

      if (text->type == GUMBO_NODE_TEXT) {
        first = text->v.text.text;
      }
    }

    if (child->v.element.tag == GUMBO_TAG_TBODY) {
      int periods = CountPeriods(child);

      GumboVector* tbody_children = &child->v.element.children;
      std::size_t tbody_children_length = tbody_children->length;
      std::vector<std::string> marks;

      for (std::size_t j = 0; j < tbody_children_length; ++j) {
        GumboNode* tbody_child =
            static_cast<GumboNode*>(tbody_children->data[j]);
        if (tbody_child->v.element.tag == GUMBO_TAG_TR) {
          GumboNode* grades_average_tag =
              static_cast<GumboNode*>(tbody_child->v.element.children.data[5]);

          if (grades_average_tag->v.element.children.length > 0) {
            GumboNode* text = static_cast<GumboNode*>(
                grades_average_tag->v.element.children.data[0]);

            if (text->type == GUMBO_NODE_TEXT) {
              marks.push_back(text->v.text.text);
            }
          } else {
            marks.push_back("");
          }
        }
      }

      try {
        second = marks.at(
            ((periods == 4) ? time_provider_.GetQuarter()
                            : ((periods == 3)   ? time_provider_.GetTrimester()
                               : (periods == 2) ? time_provider_.GetSemester()
                                                : 1)) -
            1);
      } catch (std::exception& e) {
        second = "";
      }

      if (!second.empty()) {
        average_marks[first] = second;
      }
    }
  }
}

void AverageParsingStrategy::Parse(
    std::string html,
    std::unordered_map<std::string, std::string>& average_marks) {
  std::stack<MarkupElem> mobile_path;

  mobile_path.push({"table", "table table-bordered GradesTable MobileGrades"});
  mobile_path.push({"div", "DivForGradesTable"});
  mobile_path.push({"main", "container-fluid"});
  mobile_path.push({"body", ""});

  GumboOutput* output = gumbo_parse(html.c_str());

  GumboNode* root = output->root;

  GumboNode* mobile_table = FindTag(root, mobile_path);

  FindAverageMarks(mobile_table, average_marks);

  gumbo_destroy_output(&kGumboDefaultOptions, output);
}

void TodayParsingStrategy::GetPeriodsMarks(GumboNode* tag_marks,
                                           std::string& marks) {
  GumboVector* children = &tag_marks->v.element.children;
  std::size_t children_length = children->length;

  for (std::size_t i = 0; i < children_length; ++i) {
    GumboNode* child = static_cast<GumboNode*>(children->data[i]);

    if (child->v.element.tag == GUMBO_TAG_SPAN) {
      std::string dates = (gumbo_get_attribute(&child->v.element.attributes,
                                               "data-popover-content")
                               ->value);

      std::string date = dates.substr(
          sizeof("Дата урока: 11.11.1111<p>Дата проставления: ") - 1);

      if (date == time_provider_.GetDate()) {
        GumboNode* text =
            static_cast<GumboNode*>(child->v.element.children.data[0]);
        std::string mark = text->v.text.text;
        marks += mark;
      }
    }
  }
}

void TodayParsingStrategy::FindTodayMarks(
    GumboNode* tbody,
    std::unordered_map<std::string, std::string>& today_marks) {
  GumboVector* tbody_children = &tbody->v.element.children;
  std::size_t tbody_children_length = tbody_children->length;

  for (std::size_t i = 0; i < tbody_children_length; ++i) {
    GumboNode* tbody_child = static_cast<GumboNode*>(tbody_children->data[i]);
    std::string lesson = "_";

    if (tbody_child->v.element.tag == GUMBO_TAG_TR) {
      GumboVector* tr_children = &tbody_child->v.element.children;
      std::size_t tr_children_length = tr_children->length;

      for (std::size_t j = 0; j < tr_children_length; ++j) {
        GumboNode* tr_child = static_cast<GumboNode*>(tr_children->data[j]);

        // Получение названия предмета
        if (tr_child->v.element.tag == GUMBO_TAG_TD &&
            strcmp(gumbo_get_attribute(&tr_child->v.element.attributes, "class")
                       ->value,
                   "grades-lesson") == 0) {
          GumboNode* text =
              static_cast<GumboNode*>(tr_child->v.element.children.data[0]);

          if (text->type == GUMBO_NODE_TEXT) {
            lesson = text->v.text.text;
          }
        }

        // Получение оценок за день
        if (tr_child->v.element.tag == GUMBO_TAG_TD &&
            strcmp(gumbo_get_attribute(&tr_child->v.element.attributes, "class")
                       ->value,
                   "grades-marks") == 0) {
          std::string marks = "";
          GetPeriodsMarks(tr_child, marks);

          if (!marks.empty()) {
            if (today_marks.find(lesson) != today_marks.end()) {
              today_marks[lesson] += marks;
            } else {
              today_marks[lesson] = marks;
            }
          }
        }
      }
    }
  }
}

void TodayParsingStrategy::Parse(
    std::string html,
    std::unordered_map<std::string, std::string>& today_marks) {
  std::stack<MarkupElem> full_path;

  full_path.push({"tbody", ""});
  full_path.push({"table", "table table-bordered GradesTable"});
  full_path.push({"div", "DivForGradesTable"});
  full_path.push({"main", "container-fluid"});
  full_path.push({"body", ""});

  GumboOutput* output = gumbo_parse(html.c_str());

  GumboNode* root = output->root;

  GumboNode* full_table = FindTag(root, full_path);

  FindTodayMarks(full_table, today_marks);
  
  gumbo_destroy_output(&kGumboDefaultOptions, output);
}

TodayParsingStrategy::TodayParsingStrategy(TimeProvider& time_provider)
    : time_provider_(time_provider) {}

AverageParsingStrategy::AverageParsingStrategy(TimeProvider& time_provider)
    : time_provider_(time_provider) {}

Parser::Parser(parser::Strategy parsing_strategy, TimeProvider& time_provider) {
  if (parsing_strategy == Strategy::AVERAGE_MARKS) {
    strategy_ = std::make_unique<AverageParsingStrategy>(time_provider);
  } else if (parsing_strategy == Strategy::TODAY_MARKS) {
    strategy_ = std::make_unique<TodayParsingStrategy>(time_provider);
  }
}

Parser::Parser(parser::Strategy parsing_strategy) {
  if (parsing_strategy == Strategy::AVERAGE_MARKS) {
    strategy_ = std::make_unique<AverageParsingStrategy>(time_provider_);
  } else if (parsing_strategy == Strategy::TODAY_MARKS) {
    strategy_ = std::make_unique<TodayParsingStrategy>(time_provider_);
  }
}

std::unordered_map<std::string, std::string> Parser::Parse(
    std::string html) const {
  std::unordered_map<std::string, std::string> result;

  strategy_->Parse(html, result);

  return result;
}

}  // namespace parser