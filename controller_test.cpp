#include "controller.hpp"


using std::string;


namespace {
  struct FakeUserInterface : UserInterface {
    virtual void setTags(std::string &arg) { tags = arg; }

    virtual void show() { shown = true; }

    virtual void fillList(const ListEntries &arg)
    {
      list_entries = arg;
    }

    string tags;
    bool shown = false;
    ListEntries list_entries;
  };
}


int main()
{
#if 0
  FakeUserInterface user_interface;
  FakeStorage storage;
  FakeStackExchange stack_exchange;
  Data data{storage,stack_exchange};
  Controller controller{user_interface,data};
#endif
}
