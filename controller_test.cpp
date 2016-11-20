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

    void userPressesUpdate()
    {
      updatePressed();
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

    void updateStoredQuestions(const std::string & tags) override
    {
      query_tags = tags;
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

    string query_tags;
  };
}


namespace {
  struct TestHarness {
    FakeUserInterface user_interface;
    FakeSystem system;
    Controller controller{user_interface,system};

    TestHarness()
    {
      controller.runApplication();
    }

    void testRunningApplication()
    {
      assert(user_interface.is_shown);
    }


    void testPressingUpdate()
    {
      user_interface.userPressesUpdate();
      assert(system.query_tags=="c++");
    }
  };
}


int main()
{
  TestHarness().testRunningApplication();
  TestHarness().testPressingUpdate();
}
