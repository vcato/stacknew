#include "data.hpp"
#include "qtuserinterface.hpp"
#include "controller.hpp"
#include "realsystem.hpp"


int main(int argc,char** argv)
{
  RealSystem system;
  Data data(system);

  QtUserInterface user_interface(argc,argv);
  user_interface.create();

  Controller controller{user_interface,data};
  controller.runApplication();
}
