#include "textfile.hpp"

#include <fstream>
#include <sstream>

using std::string;


void saveTextToFile(const char *path,const string &text)
{
  std::ofstream stream(path);
  // what to do if we can't open the file?
  stream << text;
}


string readTextFromFile(const char *path)
{
  std::ifstream stream(path);
  std::ostringstream output_stream;
  if (!stream) return "";
  // Need to make sure we read all the tags.
  output_stream << stream.rdbuf();
  return output_stream.str();
}
