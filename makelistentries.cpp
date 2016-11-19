#include "makelistentries.hpp"

#include "decodedstring.hpp"


using std::string;
using std::vector;


static string dateString(int64_t date_time)
{
  struct tm date_tm;
  localtime_r(&date_time,&date_tm);
  char buffer[256];
  strftime(buffer,sizeof buffer,"%Y-%m-%d %I:%M:%S %p",&date_tm);
  return buffer;
}


static bool anyQuestionHasId(int id,const vector<Question> &old_questions)
{
  for (auto& question : old_questions)
  {
    if (question.id==id) return true;
  }

  return false;
}


vector<ListEntry>
  makeListEntries(
    const vector<Question> &old_questions,
    const vector<Question> &questions
  )
{
  int n_questions = questions.size();
  vector<ListEntry> list_entries;

  for (int i=0; i!=n_questions; ++i) {
    const Question &question = questions[i];

    ListEntry list_entry;
    list_entry.title = decodedString(question.title);
    list_entry.creation_date = dateString(question.creation_date);
    list_entry.is_new = !anyQuestionHasId(question.id,old_questions);
    list_entries.push_back(list_entry);
  }

  return list_entries;
}
