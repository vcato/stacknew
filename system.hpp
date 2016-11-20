#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

struct System {
  virtual Questions readStoredOldQuestions() = 0;
  virtual Questions readStoredNewQuestions() = 0;
  virtual void updateStoredQuestions(const std::string &tags) = 0;
};

#endif /* SYSTEM_HPP_ */
