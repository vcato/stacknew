#include "qtuserinterface.hpp"
#include "controller.hpp"
#include "system.hpp"


int main(int argc,char** argv)
{
  QtUserInterface user_interface(argc,argv);
  System system;
  Controller controller{user_interface,system};

  controller.runApplication();
}
