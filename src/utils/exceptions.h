#pragma once

#include <exception>
#include <string>

namespace exceptions {

class ParsingException : public std::exception {
 public:
  ParsingException(const std::string& error_message)
      : error_message_(error_message) {}
  ParsingException() = default;
  ~ParsingException() = default;

  const char* what() const throw() override { return error_message_.c_str(); }

 private:
  std::string error_message_;
};

class TokenException : public std::exception {
 public:
  TokenException(const std::string& error_message)
      : error_message_(error_message) {}
  TokenException() = default;
  ~TokenException() = default;

  const char* what() const throw() override { return error_message_.c_str(); }

 private:
  std::string error_message_;
};

class UserException : public std::exception {
 public:
  UserException(const std::string& error_message)
      : error_message_(error_message) {}
  UserException() = default;
  ~UserException() = default;

  const char* what() const throw() override { return error_message_.c_str(); }

 private:
  std::string error_message_;
};
} // namespace exceptions