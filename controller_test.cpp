#include "controller.hpp"

#include <iostream>
#include <cassert>


using std::string;
using std::cerr;


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
  struct FakeSystem : System {
    virtual Questions readStoredOldQuestions()
    {
      assert(false);
    }

    virtual Questions readStoredNewQuestions()
    {
      assert(false);
    }

    virtual void updateStoredQuestions(const std::string &tags)
    {
      cerr << "tags=" << tags << "\n";
      assert(false);
    }

    virtual void playNewQuestionsSound()
    {
      assert(false);
    }
  };
}


int main()
{
#if 0
  FakeUserInterface user_interface;
  FakeSystem system;
  Controller controller{user_interface,system};
#endif
}
