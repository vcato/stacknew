#ifndef QUESTION_HPP_
#define QUESTION_HPP_

#include <string>

struct Question {
  std::string title;
  std::string link;
  int64_t creation_date;
  int id;
};

#endif /* QUESTION_HPP_ */
