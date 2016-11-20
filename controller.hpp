#include "userinterface.hpp"
#include "system.hpp"


class Controller {
  public:
    Controller(
      UserInterface& user_interface_arg,
      System& system_arg
    );

    void runApplication();

    static std::string defaultTags() { return "c++ c++11 c++14 c++17"; }

  private:
    struct Data {
      void readExisting(System&);
      void update(System&,const std::string &tags);

      Questions old_questions;
      Questions new_questions;
    };

    UserInterface &user_interface;
    System &system;
    Data data;

    void rowClicked(size_t row);
    void updatePressed();
    bool updateList();
};
