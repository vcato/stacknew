#include "textfile.hpp"

#include <cassert>
#include <iostream>

using std::string;
using std::cerr;


int main()
{
  const char *temp_path = "textfile_test.txt";
  string original_text = "some text";
  saveTextToFile(temp_path,original_text);
  string result = readTextFromFile(temp_path);
  assert(result==original_text);
  remove(temp_path);
}
