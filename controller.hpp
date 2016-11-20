#include "userinterface.hpp"
#include "system.hpp"


class Controller {
  public:
    Controller(
      UserInterface& user_interface_arg,
      System& system_arg
    );

    void runApplication();

  private:
    struct Data {
      Data(System&);

      void readExisting(System&);
      void update(System&,const std::string &tags);

      Questions old_questions;
      Questions new_questions;
    };

    UserInterface &user_interface;
    Data data;
    System &system;

    void rowClicked(int row);
    void updatePressed();
    bool updateList();
};
