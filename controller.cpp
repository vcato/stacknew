#include "controller.hpp"

#include "playsound.hpp"
#include "openlink.hpp"
#include "makelistentries.hpp"


static void playNewQuestionsSound()
{
  playSound("/usr/share/scratch/Media/Sounds/Effects/Pop.wav");
}


static bool anyAreNew(const ListEntries &new_entries)
{
  for (const auto& entry : new_entries) {
    if (entry.is_new) return true;
  }

  return false;
}


Controller::Controller(UserInterface &user_interface_arg,Data &data_arg)
: user_interface(user_interface_arg),
  data(data_arg)
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
  openLink(data.new_questions[row].link);
}


void Controller::updatePressed()
{
  data.update();
  bool any_are_new = updateList();

  if (any_are_new) {
    playNewQuestionsSound();
  }
}


bool Controller::updateList()
{
  ListEntries entries = makeListEntries(data.old_questions,data.new_questions);
  user_interface.fillList(entries);
  return anyAreNew(entries);
}
