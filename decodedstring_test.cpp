#include "decodedstring.hpp"

#include <cassert>


static void testDecodedString()
{
  assert(decodedString("&gt;")==">");
  assert(decodedString("&gt;&gt;")==">>");
}


int main()
{
  testDecodedString();
}
