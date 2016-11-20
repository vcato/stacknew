#ifndef DATA_HPP_
#define DATA_HPP_

#include "questions.hpp"


class Data {
  public:
    Data();

    void readExisting();
    void update();

    Questions old_questions;
    Questions new_questions;
    std::string tags;

  private:
    Questions readOldQuestions();
    Questions readNewQuestions();
};

#endif /* DATA_HPP_ */
