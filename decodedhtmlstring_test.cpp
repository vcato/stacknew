#include "decodedhtmlstring.hpp"

#include <cassert>


static void testDecodedString()
{
  assert(decodedHTMLString("&gt;")==">");
  assert(decodedHTMLString("&gt;&gt;")==">>");
  assert(decodedHTMLString("&lt;")=="<");
  assert(decodedHTMLString("tm &amp; time_t")=="tm & time_t");
}


int main()
{
  testDecodedString();
}
