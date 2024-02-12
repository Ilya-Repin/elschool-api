#include "mocked_time_provider.hpp"

int MockedTimeProvider::GetMonth() { return month_; }

  int MockedTimeProvider::GetSemester() {
    int month = GetMonth();
    if (month >= 1 && month <= 6) {
      return 1;
    } else if (month >= 9 && month <= 12) {
      return 2;
    } else {
      return 0;
    }
  }

  int MockedTimeProvider::GetTrimester() {
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

  int MockedTimeProvider::GetQuarter() {
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

std::string MockedTimeProvider::GetDate() {
  return date_;
}

void MockedTimeProvider::SetMonth(int month) {
  month_ = month;
}

void MockedTimeProvider::SetDate(std::string date) {
  date_ = date;
}