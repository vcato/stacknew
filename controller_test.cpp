#include "controller.hpp"


using std::string;


namespace {
  struct FakeUserInterface : UserInterface {
    virtual void setTags(std::string &arg) { tags = arg; }

    string tags;
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
