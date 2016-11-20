#include "replacedstring.hpp"


using std::string;
using std::vector;


string replacedString(const string &arg,const vector<Replacement> &replacements)
{
  string s = arg;

  for (size_t index = 0; index!=s.size(); ++index) {
    for (const auto& r : replacements) {

      if (s.compare(index,r.old_string.size(),r.old_string)==0) {
        s.replace(index,r.old_string.size(),r.new_string);
      }
    }
  }

  return s;
}


