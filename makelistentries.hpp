#ifndef MAKELISTENTRIES_HPP_
#define MAKELISTENTRIES_HPP_

#include "questions.hpp"
#include "listentries.hpp"

extern ListEntries
  makeListEntries(
    const Questions &old_questions,
    const Questions &new_questions
  );

#endif /* MAKELISTENTRIES_HPP_ */
