#ifndef _MY_EXCEPTION_H_
#define _MY_EXCEPTION_H_

#include <exception>
#include <iostream>

class MyException : public std::exception {
 public:
  MyException(std::string error) : error_{error} {};
  const char* what() const noexcept override { return this->error_.c_str(); };

 private:
  std::string error_;
};

#endif  //_MY_EXCEPTION_H_