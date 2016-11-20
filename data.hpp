#ifndef DATA_HPP_
#define DATA_HPP_

#include "questions.hpp"
#include "system.hpp"


class Data {
  public:
    Data(System &);

    void readExisting();
    void update();

    System &system;
    Questions old_questions;
    Questions new_questions;
    std::string tags;
};


#endif /* DATA_HPP_ */
