#include "decodedstring.hpp"

#include <cassert>


static void testDecodedString()
{
  assert(decodedString("&gt;")==">");
  assert(decodedString("&gt;&gt;")==">>");
  assert(decodedString("&lt;")=="<");
}


int main()
{
  testDecodedString();
}
