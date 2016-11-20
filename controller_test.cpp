#include "controller.hpp"

#include <iostream>
#include <cassert>


using std::string;
using std::cerr;


namespace {
  struct FakeUserInterface : UserInterface {
    virtual void setTagsString(const std::string &arg) { tags = arg; }
    virtual std::string tagsString() { return tags; }

    virtual void show() { is_shown = true; }

    virtual void fillList(const ListEntries &arg)
    {
      list_entries = arg;
    }

    void userChangesTagsTo(const string &tags_arg)
    {
      tags = tags_arg;
    }

    void userDoubleClicksOnRow(size_t row)
    {
      assert(row<list_entries.size());
      rowClicked(row);
    }

    void enableTimeouts()
    {
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
      return stored_new_questions;
    }

    void updateStoredQuestions(const std::string & tags) override
    {
      query_tags = tags;
      stored_new_questions = pending_questions;
      ++query_count;
    }

    void playNewQuestionsSound() override
    {
      new_questions_sound_was_played = true;
    }

    void openLink(const std::string &link) override
    {
      opened_link = link;
    }

    double currentTime() override
    {
      return current_time;
    }

    string query_tags;
    string opened_link;
    double current_time = 0;
    Questions stored_new_questions;
    Questions pending_questions;
    bool new_questions_sound_was_played = false;
    int query_count = 0;
  };
}


namespace {
  struct TestHarness {
    FakeUserInterface user_interface;
    FakeSystem system;
    Controller controller{user_interface,system};

    TestHarness()
    {
    }

    void testRunningApplication()
    {
      controller.runApplication();
      assert(user_interface.is_shown);
    }


    void testPressingUpdate()
    {
      controller.runApplication();
      user_interface.updatePressed();
      assert(system.query_tags==Controller::defaultTags());
    }


    void testChangingTagsAndPressingUpdate()
    {
      controller.runApplication();
      user_interface.userChangesTagsTo("c++ c++14");
      user_interface.updatePressed();
      assert(system.query_tags=="c++ c++14");
    }

    void testNewQuestionsMakeASound()
    {
      controller.runApplication();
      system.pending_questions = {
        {"title","link",1234,1}
      };
      user_interface.updatePressed();
      assert(system.new_questions_sound_was_played);
    }

    void testOpeningAQuestion()
    {
      system.stored_new_questions = {
        {"title","link",1234,1}
      };
      controller.runApplication();
      user_interface.userDoubleClicksOnRow(0);
      assert(system.opened_link == "link");
    }

    void testAutomaticUpdates()
    {
      system.current_time = 100;
      controller.runApplication();
      user_interface.updatePressed();
      system.current_time = 100+60;
      system.query_count = 0;
      user_interface.timeoutOccurred();
      assert(system.query_count==1);
    }
  };
}


int main()
{
  TestHarness().testRunningApplication();
  TestHarness().testPressingUpdate();
  TestHarness().testChangingTagsAndPressingUpdate();
  TestHarness().testNewQuestionsMakeASound();
  TestHarness().testOpeningAQuestion();
  TestHarness().testAutomaticUpdates();
}
