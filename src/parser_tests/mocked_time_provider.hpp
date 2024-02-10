#include "../parser/parser.hpp"

class MockedTimeProvider : public parser::TimeProvider {
 public:
  int GetMonth();
  int GetSemester();
  int GetTrimester();
  int GetQuarter();
  std::string GetDate();

  void SetMonth(int month);
  void SetDate(std::string date);

 private:
  int month_;
  std::string date_;
};
