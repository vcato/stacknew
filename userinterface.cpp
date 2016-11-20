#include "userinterface.hpp"

#include <iostream>
#include <cassert>


using std::cerr;
using EventHandler = UserInterface::EventHandler;


EventHandler& UserInterface::eventHandler()
{
  assert(event_handler_ptr);
  return *event_handler_ptr;
}


void UserInterface::setEventHandler(EventHandler *arg)
{
  event_handler_ptr = arg;
}
