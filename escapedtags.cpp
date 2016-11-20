#include "escapedtags.hpp"

#include <vector>
#include "replacedstring.hpp"

using std::string;
using std::vector;



static const vector<Replacement> replacements = {
  {"+","%2B"},
  {" ",";"}
};


string escapedTags(const string &tags)
{
  return replacedString(tags,replacements);
}
