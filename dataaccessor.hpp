#include "questions.hpp"


struct DataAccessor {
  protected:
    Questions readStoredOldQuestions();
    Questions readStoredNewQuestions();
    void updateStoredQuestions(const std::string &tags);
};
