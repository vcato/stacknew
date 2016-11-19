#include "data.hpp"
#include "userinterface.hpp"
#include "controller.hpp"


int main(int argc,char** argv)
{
  Data data;

  UserInterface user_interface(argc,argv);
  user_interface.create();

  Controller controller{user_interface,data};
  controller.runApplication();
}
