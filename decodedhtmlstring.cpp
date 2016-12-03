#include "decodedhtmlstring.hpp"

#include <vector>
#include "replacedstring.hpp"


using std::string;
using std::vector;


static const vector<Replacement> replacements = {
  {"&gt;",   ">"},
  {"&lt;",   "<"},
  {"&quot;", "\""},
  {"&#39;",  "'"},
  {"&amp;",  "&"}
};


string decodedHTMLString(string s)
{
  return replacedString(s,replacements);
}
