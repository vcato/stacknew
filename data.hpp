#ifndef DATA_HPP_
#define DATA_HPP_

#include "questions.hpp"
#include "dataaccessor.hpp"


class Data : public DataAccessor {
  public:
    Data();

    void readExisting();
    void update();

    Questions old_questions;
    Questions new_questions;
    std::string tags;
};


#endif /* DATA_HPP_ */
