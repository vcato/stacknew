#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "questions.hpp"

struct System {
  virtual Questions readStoredOldQuestions() = 0;
  virtual Questions readStoredNewQuestions() = 0;
  virtual int retrieveLatestQuestions(const std::string &tags) = 0;
  virtual void updateNewQuestions() = 0;
  virtual void playNewQuestionsSound() = 0;
  virtual void openLink(const std::string &link) = 0;
  virtual double currentTime() = 0;
};

#endif /* SYSTEM_HPP_ */
