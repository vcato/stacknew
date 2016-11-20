#include "questions.hpp"
#include "system.hpp"


struct RealSystem : System {
  Questions readStoredOldQuestions() override;
  Questions readStoredNewQuestions() override;
  void updateStoredQuestions(const std::string &tags) override;
};