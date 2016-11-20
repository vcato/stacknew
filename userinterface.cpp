#include "userinterface.hpp"

#include <iostream>


using std::cerr;


void UserInterface::updatePressed()
{
  update_func();
}


void UserInterface::rowClicked(size_t row)
{
  row_clicked_func(row);
}


void UserInterface::timeoutOccurred()
{
  timeout_func();
}
