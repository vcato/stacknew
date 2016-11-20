#include "questions.hpp"


struct DataAccessor {
  Questions readStoredOldQuestions();
  Questions readStoredNewQuestions();
  void updateStoredQuestions(const std::string &tags);
};
