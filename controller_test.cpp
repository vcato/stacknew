#include "controller.hpp"

#include <iostream>
#include <cassert>


using std::string;
using std::cerr;


namespace {
  struct FakeUserInterface : UserInterface {
    virtual void setTags(std::string &arg) { tags = arg; }

    virtual void show() { is_shown = true; }

    virtual void fillList(const ListEntries &arg)
    {
      list_entries = arg;
    }

    string tags;
    bool is_shown = false;
    ListEntries list_entries;
  };
}


namespace {
  struct FakeSystem : System {
    Questions readStoredOldQuestions() override
    {
      return {};
    }

    Questions readStoredNewQuestions() override
    {
      return {};
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


static void testRunningApplication()
{
  FakeUserInterface user_interface;
  FakeSystem system;
  Controller controller{user_interface,system};
  controller.runApplication();
  assert(user_interface.is_shown);
}


int main()
{
  testRunningApplication();
}
