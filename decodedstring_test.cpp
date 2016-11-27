#include "decodedstring.hpp"

#include <cassert>


static void testDecodedString()
{
  assert(decodedString("&gt;")==">");
  assert(decodedString("&gt;&gt;")==">>");
  assert(decodedString("&lt;")=="<");
  assert(decodedString("tm &amp; time_t")=="tm & time_t");
}


int main()
{
  testDecodedString();
}
