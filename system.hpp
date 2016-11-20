#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "questions.hpp"

struct System {
  virtual Questions readStoredOldQuestions() = 0;
  virtual Questions readStoredNewQuestions() = 0;
  virtual void updateStoredQuestions(const std::string &tags) = 0;
  virtual void playNewQuestionsSound() = 0;
};

#endif /* SYSTEM_HPP_ */
