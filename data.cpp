#include "data.hpp"


Data::Data(System &system_arg)
: system(system_arg),
  tags("c++")
{
  readExisting();
}


void Data::readExisting()
{
  old_questions = system.readStoredOldQuestions();
  new_questions = system.readStoredNewQuestions();
}


void Data::update()
{
  system.updateStoredQuestions(tags);
  old_questions = new_questions;
  new_questions = system.readStoredNewQuestions();
}
