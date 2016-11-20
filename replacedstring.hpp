#include <string>
#include <vector>


struct Replacement {
  std::string old_string, new_string;
};


extern std::string
  replacedString(
    const std::string &arg,
    const std::vector<Replacement> &replacements
  );
