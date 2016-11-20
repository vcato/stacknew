#include "decodedstring.hpp"

#include <iostream>


using std::string;
using std::cerr;


string decodedString(string s)
{
  for (size_t index = 0; index!=s.size(); ++index) {
    if (s.compare(index,4,"&gt;")==0) {
      s.replace(index,4,">");
    }
    if (s.compare(index,4,"&lt;")==0) {
      s.replace(index,4,"<");
    }
    if (s.compare(index,6,"&quot;")==0) {
      s.replace(index,6,"\"");
    }
    if (s.compare(index,5,"&#39;")==0) {
      s.replace(index,5,"'");
    }
  }

  return s;
}
