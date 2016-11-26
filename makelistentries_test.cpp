#include "makelistentries.hpp"

#include <cassert>

using std::vector;


static void testWithNoQuestions()
{
  Questions old_questions;
  Questions new_questions;
  vector<ListEntry> list_entries = makeListEntries(old_questions,new_questions);
  assert(list_entries.size()==0);
}


static void testWithOneNewQuestion()
{
  Questions old_questions;
  Questions new_questions;

  Question question1;
  question1.id = 1;
  Question question2;
  question2.id = 2;
  Question question3;
  question3.id = 3;

  old_questions.push_back(question1);
  old_questions.push_back(question2);
  new_questions.push_back(question2);
  new_questions.push_back(question3);

  vector<ListEntry> list_entries = makeListEntries(old_questions,new_questions);
  assert(list_entries.size()==2);
  assert(list_entries[0].is_new==false);
  assert(list_entries[1].is_new==true);
}


int main()
{
  testWithNoQuestions();
  testWithOneNewQuestion();
}
