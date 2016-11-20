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


namespace {
  struct FakeDataAccessor : DataAccessor {
  };
}


int main()
{
#if 0
  FakeUserInterface user_interface;
  FakeDataAccessor data_accessor;
  Data data{data_accessor};
  Controller controller{user_interface,data};
#endif
}
