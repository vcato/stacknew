#include "data.hpp"


Data::Data(DataAccessor &data_accessor_arg)
: data_accessor(data_accessor_arg),
  tags("c++")
{
  readExisting();
}


void Data::readExisting()
{
  old_questions = data_accessor.readStoredOldQuestions();
  new_questions = data_accessor.readStoredNewQuestions();
}


void Data::update()
{
  data_accessor.updateStoredQuestions(tags);
  old_questions = new_questions;
  new_questions = data_accessor.readStoredNewQuestions();
}
