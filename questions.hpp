#ifndef QUESTIONS_HPP_
#define QUESTIONS_HPP_


#include <vector>
#include <string>

struct Question {
  std::string title;
  std::string link;
  int64_t creation_date;
  int id;
};

using Questions = std::vector<Question>;


#endif /* QUESTIONS_HPP_ */
