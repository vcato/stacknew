#include "controller.hpp"

#include <cassert>
#include "makelistentries.hpp"


using std::string;


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
  user_interface.row_clicked_func = [&](int row) { rowClicked(row); };
  user_interface.update_func = [&]() { updatePressed(); };
}


void Controller::runApplication()
{
  data.readExisting(system);
  updateList();
  user_interface.setTagsString(defaultTags());
  user_interface.show();
}


void Controller::rowClicked(size_t row)
{
  assert(row<data.new_questions.size());
  system.openLink(data.new_questions[row].link);
}


void Controller::updatePressed()
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
