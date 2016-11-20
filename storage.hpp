#ifndef STORAGE_HPP_
#define STORAGE_HPP_

#include "questions.hpp"


struct Storage {
  virtual Questions readOldQuestions() = 0;
};

#endif /* STORAGE_HPP_ */
