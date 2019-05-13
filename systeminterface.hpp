#ifndef SYSTEMINTERFACE_HPP_
#define SYSTEMINTERFACE_HPP_

#include "questions.hpp"

struct SystemInterface {
  virtual Questions readStoredOldQuestions() = 0;
  virtual Questions readStoredNewQuestions() = 0;
  virtual int retrieveLatestQuestions(const std::string &tags) = 0;
  virtual void updateNewQuestions() = 0;
  virtual void playNewQuestionsSound() = 0;
  virtual void openLink(const std::string &link) = 0;
  virtual void saveTags(const std::string &tags) = 0;
  virtual std::string savedTags() = 0;
  virtual double currentTime() = 0;
};

#endif /* SYSTEMINTERFACE_HPP_ */
