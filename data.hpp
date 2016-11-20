#ifndef DATA_HPP_
#define DATA_HPP_

#include "questions.hpp"

struct Storage {
};


struct StackExchange {
};


struct Data {
  Data(Storage &,StackExchange &);

  void readExisting();
  void update();

  Storage &storage;
  StackExchange &stack_exchange;
  Questions old_questions;
  Questions new_questions;
  std::string tags;
};

#endif /* DATA_HPP_ */
