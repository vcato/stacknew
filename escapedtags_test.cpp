#include "escapedtags.hpp"

#include <string>
#include <cassert>

using std::string;


int main()
{
  assert(escapedTags("c++")=="c%2B%2B");
  assert(escapedTags("c++ c++14")=="c%2B%2B;c%2B%2B14");
}
