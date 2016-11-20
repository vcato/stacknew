#include "userinterface.hpp"
#include "data.hpp"


class Controller {
  public:
    Controller(UserInterface &user_interface_arg,Data &data_arg);

    void runApplication();

  private:
    UserInterface &user_interface;
    Data &data;

    void rowClicked(int row);
    void updatePressed();
    bool updateList();
};
