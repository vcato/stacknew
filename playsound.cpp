#include "playsound.hpp"


using std::string;


void playSound(const std::string &path)
{
  system(("aplay "+path).c_str());
}
