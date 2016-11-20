#include "data.hpp"


Data::Data()
: tags("c++")
{
  readExisting();
}


void Data::readExisting()
{
  old_questions = readStoredOldQuestions();
  new_questions = readStoredNewQuestions();
}


void Data::update()
{
  updateStoredQuestions(tags);
  old_questions = new_questions;
  new_questions = readStoredNewQuestions();
}
