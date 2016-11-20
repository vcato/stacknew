struct DataAccessor {
  virtual Questions readStoredOldQuestions() = 0;
  virtual Questions readStoredNewQuestions() = 0;
  virtual void updateStoredQuestions(const std::string &tags) = 0;
};
