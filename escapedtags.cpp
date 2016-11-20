#include "escapedtags.hpp"

#include <iostream>

using std::string;
using std::cerr;


string escapedTags(const string &tags)
{
  if (tags=="c++") {
    return "c%2B%2B";
  }

  return "";
}
