#include "questions.hpp"


struct RealDataAccessor : DataAccessor {
  Questions readStoredOldQuestions() override;
  Questions readStoredNewQuestions() override;
  void updateStoredQuestions(const std::string &tags) override;
};
