#include "userinterface.hpp"
#include "system.hpp"


class Controller : UserInterface::EventHandler {
  public:
    Controller(UserInterface&, System&);
    ~Controller();

    void runApplication();
    static std::string defaultTags() { return "c++ c++11 c++14 c++17"; }

    struct Data {
      void readExisting(System&);
      void update(System&,const std::string &tags);

      Questions old_questions;
      Questions new_questions;
      UpdateInterval update_interval = UpdateInterval::none();
      double last_update_time = 0;
    };

    Data data;

  private:

    UserInterface &user_interface;
    System &system;

    void rowClicked(size_t row) override;
    void updatePressed() override;
    void timeoutOccurred();
    void updateOptionSelected(int) override;

    bool updateList();
    void update();
    void checkForAutomaticUpdates();
};
