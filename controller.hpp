#include "userinterface.hpp"
#include "systeminterface.hpp"


class Controller : private UserInterface::EventHandler {
  public:
    Controller(UserInterface&, SystemInterface&);
    ~Controller();

    void runApplication();
    static std::string defaultTags() { return "c++ c++11 c++14 c++17"; }

    struct Data {
      void readExisting(SystemInterface&);
      int update(SystemInterface&,const std::string &tags);

      Questions old_questions;
      Questions new_questions;
      UpdateInterval update_interval = UpdateInterval::none();
      double last_update_time = 0;
    };

    static std::string noUpdateText();
    static std::string oneMinuteUpdateText();
    static std::string noUpdatesYetMessage();
    static std::string lastUpdateMessage(int64_t time);
    static std::string updateFailedMessage();

    Data data;

  private:
    using OptionalQuestionId = int;
    using OptionalListIndex = UserInterface::OptionalListIndex;

    static const OptionalQuestionId no_question_id = -1;

    UserInterface &user_interface;
    SystemInterface &system;

    void rowClicked(size_t row) override;
    void updatePressed() override;
    void timeoutOccurred() override;
    void updateOptionSelected(int) override;

    OptionalQuestionId optionalQuestionIdFor(OptionalListIndex);
    OptionalListIndex indexOfQuestionWithId(OptionalQuestionId);

    bool updateList();
    void update();
    void checkForAutomaticUpdates();
    void restoreSavedTags();
};
