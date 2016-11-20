#include "controller.hpp"

#include <iostream>
#include <cassert>


using std::string;
using std::cerr;
using UpdateInterval = UserInterface::UpdateInterval;
static const auto no_list_index = UserInterface::no_list_index;


namespace {
  struct FakeUserInterface : UserInterface {
    void setTagsString(const std::string &arg) override { tags = arg; }

    std::string tagsString() override { return tags; }

    void show() override { is_shown = true; }

    void fillList(const ListEntries &arg) override
    {
      list_entries = arg;
      selected_index = no_list_index;
    }

    void setUpdateOptions(const std::vector<UpdateOption> &arg) override
    {
      update_options = arg;
    }


    void userChangesTagsTo(const string &tags_arg)
    {
      tags = tags_arg;
    }

    void userDoubleClicksOnRow(size_t row)
    {
      assert(row<list_entries.size());
      eventHandler().rowClicked(row);
    }

    void userPressesUpdate()
    {
      eventHandler().updatePressed();
    }

    void timeoutOccurs()
    {
      eventHandler().timeoutOccurred();
    }

    int updateOptionWithName(const std::string &arg)
    {
      int n = update_options.size();

      for (int i=0; i!=n; ++i) {
        if (update_options[i].text==arg) {
          return i;
        }
      }

      assert(false);
    }

    void userChangesUpdateIntervalTo(const std::string &arg)
    {
      int index = updateOptionWithName(arg);
      eventHandler().updateOptionSelected(index);
    }

    void userSelectsIndex(int arg)
    {
      selected_index = arg;
    }

    void enableTimeouts()
    {
    }

    OptionalListIndex selectedListIndex()
    {
      return selected_index;
    }

    void setSelectedListIndex(OptionalListIndex arg)
    {
      selected_index = arg;
    }

    string tags;
    OptionalListIndex selected_index = no_list_index;
    bool is_shown = false;
    ListEntries list_entries;
    UpdateOptions update_options;
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
      user_interface.userPressesUpdate();
      assert(system.query_tags==Controller::defaultTags());
    }


    void testChangingTagsAndPressingUpdate()
    {
      controller.runApplication();
      user_interface.userChangesTagsTo("c++ c++14");
      user_interface.userPressesUpdate();
      assert(system.query_tags=="c++ c++14");
    }

    void testNewQuestionsMakeASound()
    {
      controller.runApplication();
      system.pending_questions = {
        {"title","link",1234,1}
      };
      user_interface.userPressesUpdate();
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
      controller.data.update_interval = UpdateInterval::inMinutes(1);
      controller.runApplication();
      user_interface.userPressesUpdate();
      system.current_time = 100+60;
      system.query_count = 0;
      user_interface.timeoutOccurs();
      assert(system.query_count==1);
    }

    void testChangingUpdateInterval()
    {
      controller.runApplication();
      system.current_time = 100;
      user_interface.userPressesUpdate();
      system.current_time = 160;
      user_interface.timeoutOccurs();
      assert(system.query_count==1);
      user_interface.userChangesUpdateIntervalTo("1 minute");
      assert(system.query_count==2);
    }

    void testSelectedItemMovesOnUpdate()
    {
      system.stored_new_questions = {
        {"title","link",1234,1}
      };
      system.pending_questions = {
        {"title","link",1234,2},
        {"title","link",1234,1}
      };
      controller.runApplication();
      user_interface.userSelectsIndex(0);
      assert(user_interface.selected_index==0);
      user_interface.userPressesUpdate();
      assert(user_interface.selected_index==1);
    }

    void testSelectedItemRemovedOnUpdate()
    {
      system.stored_new_questions = {
        {"title","link",1234,1}
      };
      system.pending_questions = {
        {"title","link",1234,2}
      };
      controller.runApplication();
      user_interface.userSelectsIndex(0);
      assert(user_interface.selected_index==0);
      user_interface.userPressesUpdate();
      assert(user_interface.selected_index==no_list_index);
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
  TestHarness().testChangingUpdateInterval();
  TestHarness().testSelectedItemMovesOnUpdate();
  TestHarness().testSelectedItemRemovedOnUpdate();
}
