#ifndef DATA_HPP_
#define DATA_HPP_

#include "questions.hpp"

struct Storage {
};


struct StackExchange {
};


class Data {
  public:
    Data(Storage &,StackExchange &);

    void readExisting();
    void update();

    Questions old_questions;
    Questions new_questions;
    std::string tags;

  private:
    Storage &storage;
    StackExchange &stack_exchange;

    Questions readOldQuestions();
    Questions readNewQuestions();
};

#endif /* DATA_HPP_ */
