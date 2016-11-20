#include "userinterface.hpp"


void UserInterface::updatePressed()
{
  update_func();
}


void UserInterface::rowClicked(size_t row)
{
  row_clicked_func(row);
}
