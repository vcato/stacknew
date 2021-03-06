#include "controller.hpp"

#include <cassert>
#include <iostream>
#include "makelistentries.hpp"
#include "datestring.hpp"


using std::string;
using std::cerr;
using std::vector;
using UpdateOption = UserInterface::UpdateOption;
using OptionalListIndex = UserInterface::OptionalListIndex;

static const auto no_list_index = UserInterface::no_list_index;
static const char *no_update_text = "None";
static const char *one_minute_update_text = "1 minute";

static const vector<UpdateOption> update_options = {
  {no_update_text,UpdateInterval::none()},
  {one_minute_update_text,UpdateInterval::fromMinutes(1)},
  {"5 minutes",UpdateInterval::fromMinutes(5)},
  {"15 minutes",UpdateInterval::fromMinutes(15)}
};


static bool anyAreNew(const ListEntries &new_entries)
{
  for (const auto& entry : new_entries) {
    if (entry.is_new) return true;
  }

  return false;
}


void Controller::Data::readExisting(SystemInterface& system)
{
  old_questions = system.readStoredOldQuestions();
  new_questions = system.readStoredNewQuestions();
}


int Controller::Data::update(SystemInterface& system,const string &tags)
{
  if (system.retrieveLatestQuestions(tags)!=EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }
  system.updateNewQuestions();
  last_update_time = system.currentTime();
  old_questions = new_questions;
  new_questions = system.readStoredNewQuestions();

  return EXIT_SUCCESS;
}


Controller::Controller(
  UserInterface& user_interface_arg,
  SystemInterface& system_arg
)
: user_interface(user_interface_arg),
  system(system_arg)
{
  user_interface.setEventHandler(this);
  user_interface.setUpdateOptions(update_options);
}


Controller::~Controller()
{
  user_interface.setEventHandler(nullptr);
}


void Controller::restoreSavedTags()
{
  string tags = system.savedTags();
  if (tags.empty()) {
    tags = defaultTags();
  }
  user_interface.setTagsString(tags);
}


void Controller::runApplication()
{
  data.readExisting(system);
  updateList();
  restoreSavedTags();
  user_interface.enableTimeouts();
  user_interface.setStatusMessage(noUpdatesYetMessage());
  user_interface.show();
}


void Controller::rowClicked(size_t row)
{
  assert(row<data.new_questions.size());
  system.openLink(data.new_questions[row].link);
}


void Controller::updatePressed()
{
  update();
}


Controller::OptionalQuestionId
  Controller::optionalQuestionIdFor(OptionalListIndex index)
{
  if (index==no_list_index) {
    return no_question_id;
  }

  return data.new_questions[index].id;
}


OptionalListIndex
  Controller::indexOfQuestionWithId(OptionalQuestionId optional_id)
{
  if (optional_id==no_question_id) {
    return no_list_index;
  }

  int n = data.new_questions.size();

  for (int i=0; i!=n; ++i) {
    if (data.new_questions[i].id==optional_id) {
      return i;
    }
  }

  return no_list_index;
}


void Controller::update()
{
  int selected_index = user_interface.selectedListIndex();
  OptionalQuestionId id = optionalQuestionIdFor(selected_index);

  string tags = user_interface.tagsString();

  if (data.update(system,tags)!=EXIT_SUCCESS) {
    int no_update_index = 0;
    user_interface.setSelectedUpdateOption(no_update_index);
    updateOptionSelected(no_update_index);
    user_interface.setStatusMessage(updateFailedMessage());
    return;
  }

  system.saveTags(tags);

  user_interface.setStatusMessage(lastUpdateMessage(data.last_update_time));
  bool any_are_new = updateList();

  if (any_are_new) {
    system.playNewQuestionsSound();
  }

  user_interface.setSelectedListIndex(indexOfQuestionWithId(id));
}


bool Controller::updateList()
{
  ListEntries entries = makeListEntries(data.old_questions,data.new_questions);
  user_interface.setListEntries(entries);
  return anyAreNew(entries);
}


void Controller::checkForAutomaticUpdates()
{
  double time_since_last_update_in_seconds =
    system.currentTime()-data.last_update_time;

  if (!data.update_interval.isNone()) {
    double update_interval_in_seconds = data.update_interval.inMinutes()*60;

    if (time_since_last_update_in_seconds>=update_interval_in_seconds) {
      update();
    }
  }
}


void Controller::timeoutOccurred()
{
  checkForAutomaticUpdates();
}


void Controller::updateOptionSelected(int index)
{
  data.update_interval = update_options[index].interval;
  checkForAutomaticUpdates();
}


string Controller::noUpdateText()
{
  return no_update_text;
}


string Controller::oneMinuteUpdateText()
{
  return one_minute_update_text;
}


string Controller::noUpdatesYetMessage()
{
  return "No updates yet.";
}


string Controller::lastUpdateMessage(int64_t last_update_time)
{
  return "Last update "+dateString(last_update_time);
}


string Controller::updateFailedMessage()
{
  return "Update failed.";
}
