#include "qtuserinterface.hpp"
#include "data.hpp"


class Controller {
  public:
    Controller(QtUserInterface &user_interface_arg,Data &data_arg);

    void runApplication();

  private:
    QtUserInterface &user_interface;
    Data &data;

    void rowClicked(int row);
    void updatePressed();
    bool updateList();
};
