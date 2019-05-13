#include "controller.hpp"

#include <iostream>
#include <cassert>


using std::string;
using std::cerr;
static const auto no_list_index = UserInterface::no_list_index;


namespace {
  struct FakeUserInterface : UserInterface {
    void setTagsString(const std::string &arg) override { tags = arg; }

    std::string tagsString() override { return tags; }

    void show() override { is_shown = true; }

    void setListEntries(const ListEntries &arg) override
    {
      list_entries = arg;
      selected_index = no_list_index;
    }

    void setUpdateOptions(const std::vector<UpdateOption> &arg) override
    {
      update_options = arg;
    }

    void setSelectedUpdateOption(int index) override
    {
      selected_update_option = index;
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
        if (update_options[i].description==arg) {
          return i;
        }
      }

      assert(false);
    }

    string updateOptionName(int index)
    {
      return update_options[index].description;
    }

    void userChangesUpdateIntervalTo(const std::string &arg)
    {
      selected_update_option = updateOptionWithName(arg);
      eventHandler().updateOptionSelected(selected_update_option);
    }

    string selectedUpdateInterval()
    {
      return updateOptionName(selected_update_option);
    }

    void userSelectsIndex(int arg)
    {
      selected_index = arg;
    }

    void enableTimeouts() override
    {
    }

    OptionalListIndex selectedListIndex() override
    {
      return selected_index;
    }

    void setSelectedListIndex(OptionalListIndex arg) override
    {
      selected_index = arg;
    }

    void setStatusMessage(const std::string &arg) override
    {
      status_message = arg;
    }

    bool is_shown = false;
    string tags;
    UpdateOptions update_options;
    string status_message;
    int selected_update_option = 0;
    OptionalListIndex selected_index = no_list_index;
    ListEntries list_entries;
  };
}


namespace {
  struct FakeSystem : SystemInterface {
    Questions readStoredOldQuestions() override
    {
      return {};
    }

    Questions readStoredNewQuestions() override
    {
      return stored_new_questions;
    }

    int retrieveLatestQuestions(const string &tags) override
    {
      tags_from_last_query = tags;
      ++query_count;

      if (!can_retrieve) {
        return EXIT_FAILURE;
      }

      return EXIT_SUCCESS;
    }

    void updateNewQuestions() override
    {
      stored_old_questions = stored_new_questions;
      stored_new_questions = pending_questions;
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

    void saveTags(const std::string &arg) override
    {
      saved_tags = arg;
    }

    virtual std::string savedTags() override
    {
      return saved_tags;
    }

    string tags_from_last_query;
    string saved_tags;
    string opened_link;
    double current_time = 0;
    Questions stored_new_questions;
    Questions stored_old_questions;
    Questions pending_questions;
    bool can_retrieve = true;
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
      assert(user_interface.status_message==controller.noUpdatesYetMessage());
    }


    void testPressingUpdate()
    {
      controller.runApplication();
      user_interface.userPressesUpdate();
      assert(system.tags_from_last_query==Controller::defaultTags());
      assert(
        user_interface.status_message ==
        controller.lastUpdateMessage(system.current_time)
      );
    }

    void testTagsAreSaved()
    {
      controller.runApplication();
      user_interface.userChangesTagsTo("python");
      assert(user_interface.tags!=Controller::defaultTags());
      user_interface.userPressesUpdate();
      assert(system.saved_tags=="python");
    }


    void testChangingTagsAndPressingUpdate()
    {
      controller.runApplication();
      user_interface.userChangesTagsTo("c++ c++14");
      user_interface.userPressesUpdate();
      assert(system.tags_from_last_query=="c++ c++14");
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
      userChangesUpdateIntervalToOneMinute();
      controller.runApplication();
      user_interface.userPressesUpdate();
      system.query_count = 0;
      currentTimeChangesTo(100+60);
      assert(system.query_count==1);
    }

    void testChangingUpdateInterval()
    {
      controller.runApplication();
      system.current_time = 100;
      user_interface.userPressesUpdate();
      currentTimeChangesTo(160);
      assert(system.query_count==1);
      userChangesUpdateIntervalToOneMinute();
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

    void testRetrieveFailure()
    {
      system.stored_new_questions = {
        {"title","link",1234,1}
      };
      controller.runApplication();
      ListEntries old_list_entries = user_interface.list_entries;
      system.can_retrieve = false;
      user_interface.userPressesUpdate();
      assert(user_interface.list_entries==old_list_entries);
      assert(user_interface.status_message==controller.updateFailedMessage());
    }

    void testRetrieveFailure2()
    {
      system.stored_new_questions = {
        {"title","link",1234,1}
      };
      controller.runApplication();
      userChangesUpdateIntervalToOneMinute();
      currentTimeChangesTo(60);
      assert(system.query_count==1);
      system.can_retrieve = false;
      currentTimeChangesTo(120);
      assert(system.query_count==2);
      assert(
        user_interface.selectedUpdateInterval()==controller.noUpdateText()
      );
      currentTimeChangesTo(180);
      assert(system.query_count==2);
    }

    private:
      void userChangesUpdateIntervalToOneMinute()
      {
        user_interface.userChangesUpdateIntervalTo(
          controller.oneMinuteUpdateText()
        );
      }

      void currentTimeChangesTo(double arg)
      {
        system.current_time = arg;
        user_interface.timeoutOccurs();
      }
  };
}

namespace {
  struct FakeApplication {
    FakeUserInterface user_interface;
    Controller controller;

    FakeApplication(FakeSystem &system)
    : controller{user_interface,system}
    {
      controller.runApplication();
    }
  };
}


static void testSavedTagsAreReloaded()
{
  FakeSystem system;

  {
    FakeApplication app(system);
    assert(app.user_interface.tags==Controller::defaultTags());
    app.user_interface.userChangesTagsTo("python C++");
    app.user_interface.userPressesUpdate();
  }

  {
    FakeApplication app(system);
    assert(app.user_interface.tags=="python C++");
  }
}


int main()
{
  TestHarness().testRunningApplication();
  TestHarness().testPressingUpdate();
  TestHarness().testTagsAreSaved();
  TestHarness().testChangingTagsAndPressingUpdate();
  TestHarness().testNewQuestionsMakeASound();
  TestHarness().testOpeningAQuestion();
  TestHarness().testAutomaticUpdates();
  TestHarness().testChangingUpdateInterval();
  TestHarness().testSelectedItemMovesOnUpdate();
  TestHarness().testSelectedItemRemovedOnUpdate();
  TestHarness().testRetrieveFailure();
  TestHarness().testRetrieveFailure2();
  testSavedTagsAreReloaded();
}
