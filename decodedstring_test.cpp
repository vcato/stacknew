#include "decodedstring.hpp"

#include <cassert>


int main()
{
  assert(decodedString("&gt;")==">");
  assert(decodedString("&gt;&gt;")==">>");
  assert(decodedString("&lt;")=="<");
  assert(decodedString("tm &amp; time_t")=="tm & time_t");
}
