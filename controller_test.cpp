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
    Questions readStoredOldQuestions() override
    {
      assert(false);
    }

    Questions readStoredNewQuestions() override
    {
      assert(false);
    }

    void updateStoredQuestions(const std::string &tags) override
    {
      cerr << "tags=" << tags << "\n";
      assert(false);
    }

    void playNewQuestionsSound() override
    {
      assert(false);
    }

    void openLink(const std::string &link) override
    {
      cerr << "link=" << link << "\n";
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
