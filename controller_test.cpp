#include "controller.hpp"


namespace {
  struct FakeUserInterface : UserInterface {
  };
}


int main()
{
#if 0
  FakeUserInterface user_interface;
  Data data;
  Controller controller{user_interface,data};
#endif
}
