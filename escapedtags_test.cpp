#include "escapedtags.hpp"

#include <string>
#include <cassert>

using std::string;


int main()
{
  string tags = "c++";
  string escaped_tags = escapedTags(tags);
  assert(escaped_tags=="c%2B%2B");
}
