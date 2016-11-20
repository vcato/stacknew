#include "controller.hpp"

#include <cassert>
#include <iostream>
#include "makelistentries.hpp"


using std::string;
using std::cerr;
using std::vector;
using UpdateInterval = UserInterface::UpdateInterval;
using UpdateOption = UserInterface::UpdateOption;

static const vector<UpdateOption> update_options = {
  {"None",UpdateInterval::none},
  {"1 minute",UpdateInterval::inMinutes(1)}
};


static bool anyAreNew(const ListEntries &new_entries)
{
  for (const auto& entry : new_entries) {
    if (entry.is_new) return true;
  }

  return false;
}


void Controller::Data::readExisting(System& system)
{
  old_questions = system.readStoredOldQuestions();
  new_questions = system.readStoredNewQuestions();
}


void Controller::Data::update(System& system,const string &tags)
{
  system.updateStoredQuestions(tags);
  last_update_time = system.currentTime();
  old_questions = new_questions;
  new_questions = system.readStoredNewQuestions();
}


Controller::Controller(
  UserInterface& user_interface_arg,
  System& system_arg
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


void Controller::runApplication()
{
  data.readExisting(system);
  updateList();
  user_interface.setTagsString(defaultTags());
  user_interface.enableTimeouts();
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


void Controller::update()
{
  string tags = user_interface.tagsString();
  data.update(system,tags);
  bool any_are_new = updateList();

  if (any_are_new) {
    system.playNewQuestionsSound();
  }
}


bool Controller::updateList()
{
  ListEntries entries = makeListEntries(data.old_questions,data.new_questions);
  user_interface.fillList(entries);
  return anyAreNew(entries);
}


void Controller::checkForAutomaticUpdates()
{
  double time_since_last_update_in_seconds =
    system.currentTime()-data.last_update_time;
  cerr.setf(std::ios::fixed);

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
