#include "data.hpp"
#include "qtuserinterface.hpp"
#include "controller.hpp"


int main(int argc,char** argv)
{
  Data data;

  QtUserInterface user_interface(argc,argv);
  user_interface.create();

  Controller controller{user_interface,data};
  controller.runApplication();
}
