#include "decodedstring.hpp"

#include <vector>
#include "replacedstring.hpp"


using std::string;
using std::vector;


static const vector<Replacement> replacements = {
  {"&gt;",   ">"},
  {"&lt;",   "<"},
  {"&quot;", "\""},
  {"&#39;",  "'"}
};


string decodedString(string s)
{
  return replacedString(s,replacements);
}
