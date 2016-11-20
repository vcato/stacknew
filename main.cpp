#include "data.hpp"
#include "qtuserinterface.hpp"
#include "controller.hpp"


namespace {
  struct RealStorage : Storage {
  };
}


namespace {
  struct RealStackExchange : StackExchange {
  };
}


int main(int argc,char** argv)
{
  RealStorage storage;
  RealStackExchange stack_exchange;
  Data data{storage,stack_exchange};

  QtUserInterface user_interface(argc,argv);
  user_interface.create();

  Controller controller{user_interface,data};
  controller.runApplication();
}
