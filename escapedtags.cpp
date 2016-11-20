#include "escapedtags.hpp"

#include <iostream>

using std::string;
using std::cerr;


string escapedTags(const string &tags)
{
  string s = tags;

  for (size_t index = 0; index!=s.size(); ++index) {
    if (s.compare(index,1,"+")==0) {
      s.replace(index,1,"%2B");
    }
    if (s.compare(index,1," ")==0) {
      s.replace(index,1,";");
    }
  }

  return s;
}
