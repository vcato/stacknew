#include "data.hpp"
#include "qtuserinterface.hpp"
#include "controller.hpp"


int main(int argc,char** argv)
{
  DataAccessor data_accessor;
  Data data(data_accessor);

  QtUserInterface user_interface(argc,argv);
  user_interface.create();

  Controller controller{user_interface,data};
  controller.runApplication();
}
