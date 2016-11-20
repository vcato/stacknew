#ifndef LISTENTRIES_HPP_
#define LISTENTRIES_HPP_

#include <vector>
#include <string>


struct ListEntry {
  std::string title;
  std::string creation_date;
  bool is_new = false;
};


using ListEntries = std::vector<ListEntry>;

#endif /* LISTENTRIES_HPP_ */
