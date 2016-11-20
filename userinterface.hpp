class UserInterface {
  public:
    std::function<void(int row)> row_clicked_func;
    std::function<void()>        update_func;
};
