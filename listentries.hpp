#ifndef LISTENTRIES_HPP_
#define LISTENTRIES_HPP_

#include <vector>
#include <string>


struct ListEntry {
  std::string title;
  std::string creation_date;
  bool is_new = false;

  bool operator==(const ListEntry &arg) const
  {
    return
      title         == arg.title &&
      creation_date == arg.creation_date &&
      is_new        == arg.is_new;
  }
};


using ListEntries = std::vector<ListEntry>;

#endif /* LISTENTRIES_HPP_ */
