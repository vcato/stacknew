#include "qtuserinterface.hpp"
#include "controller.hpp"
#include "realsystem.hpp"


int main(int argc,char** argv)
{
  QtUserInterface user_interface(argc,argv);
  RealSystem system;
  Controller controller{user_interface,system};

  controller.runApplication();
}
