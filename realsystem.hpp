#include "questions.hpp"
#include "systeminterface.hpp"


struct RealSystem : SystemInterface {
  Questions readStoredOldQuestions() override;
  Questions readStoredNewQuestions() override;
  void playNewQuestionsSound() override;
  void openLink(const std::string &link) override;
  double currentTime() override;
  int retrieveLatestQuestions(const std::string &tags) override;
  void updateNewQuestions() override;
  void saveTags(const std::string &tags) override;
  std::string savedTags() override;
};
