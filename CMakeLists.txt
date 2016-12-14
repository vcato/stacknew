cmake_minimum_required(VERSION 2.6)
project(stacknew)
add_executable(stacknew
  main.cpp
  qtuserinterface.cpp
  userinterface.cpp
  controller.cpp
  realsystem.cpp
  textfile.cpp
  datestring.cpp
  escapedtags.cpp
  makelistentries.cpp
  replacedstring.cpp
  decodedhtmlstring.cpp
)
find_package(Qt4)
find_library(Poco_LIBRARIES
  NAMES PocoFoundation PocoNet
  PATH_SUFFIXES ${POCO_DIR}/lib
)
#find_library(Poco_LIBRARIES
#  NAMES PocoFoundationmt PocoNetmt
#  PATH_SUFFIXES ${POCO_DIR}/lib
#)
include(${QT_USE_FILE})
set_property(TARGET stacknew PROPERTY CXX_STANDARD 11)
set_property(TARGET stacknew PROPERTY AUTOMOC ON)
target_link_libraries(stacknew
  ${QT_LIBRARIES}
  PocoNet
  PocoFoundation
  jsoncpp
)
