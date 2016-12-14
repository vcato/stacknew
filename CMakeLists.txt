cmake_minimum_required(VERSION 2.6)
enable_testing()
project(stacknew)
set(CMAKE_CXX_STANDARD 11)

set_property(TARGET stacknew PROPERTY AUTOMOC ON)
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

add_executable(controller_test
  controller_test.cpp
  controller.cpp
  userinterface.cpp
  datestring.cpp
  makelistentries.cpp
  decodedhtmlstring.cpp
  replacedstring.cpp
)
add_test(controller controller_test)

add_executable(makelistentries_test
  makelistentries_test.cpp
  makelistentries.cpp
  decodedhtmlstring.cpp
  replacedstring.cpp
  datestring.cpp
)
add_test(makelistentries makelistentries_test)

add_executable(escapedtags_test
  escapedtags_test.cpp
  escapedtags.cpp
  replacedstring.cpp
)
add_test(escapedtags escapedtags_test)

add_executable(decodedhtmlstring_test
  decodedhtmlstring_test.cpp
  decodedhtmlstring.cpp
  replacedstring.cpp
)
add_test(decodedhtmlstring decodedhtmlstring_test)

add_executable(textfile_test
   textfile_test.cpp
   textfile.cpp
)
add_test(textfile textfile_test)

find_package(Qt4)
find_library(Poco_LIBRARIES
  NAMES PocoFoundation PocoNet
  PATH_SUFFIXES ${POCO_DIR}/lib
)
include(${QT_USE_FILE})
target_link_libraries(stacknew
  ${QT_LIBRARIES}
  PocoNet
  PocoFoundation
  jsoncpp
)
add_custom_target(
  run_tests ALL ctest
  DEPENDS
    stacknew
    controller_test
    makelistentries_test
    escapedtags_test
    decodedhtmlstring_test
    textfile_test
)
