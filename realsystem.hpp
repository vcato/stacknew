#include "questions.hpp"
#include "system.hpp"


struct RealSystem : System {
  Questions readStoredOldQuestions() override;
  Questions readStoredNewQuestions() override;
  void playNewQuestionsSound() override;
  void openLink(const std::string &link) override;
  double currentTime() override;
  int retrieveLatestQuestions(const std::string &tags) override;
  void updateNewQuestions() override;
};
