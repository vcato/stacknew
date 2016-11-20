#include "storage.hpp"


struct RealStorage : Storage {
  Questions readOldQuestions() override;
};
