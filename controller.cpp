#include "controller.hpp"

#include "playsound.hpp"
#include "makelistentries.hpp"


static bool anyAreNew(const ListEntries &new_entries)
{
  for (const auto& entry : new_entries) {
    if (entry.is_new) return true;
  }

  return false;
}


Controller::Data::Data(System& system)
: tags("c++")
{
  readExisting(system);
}


void Controller::Data::readExisting(System& system)
{
  old_questions = system.readStoredOldQuestions();
  new_questions = system.readStoredNewQuestions();
}


void Controller::Data::update(System& system)
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
  data(system_arg),
  system(system_arg)
{
  user_interface.row_clicked_func = [&](int row) { rowClicked(row); };
  user_interface.update_func = [&]() { updatePressed(); };
  updateList();
  user_interface.setTags(data.tags);
}


void Controller::runApplication()
{
  user_interface.show();
}


void Controller::rowClicked(int row)
{
  system.openLink(data.new_questions[row].link);
}


void Controller::updatePressed()
{
  data.update(system);
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
