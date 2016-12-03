HEADERS=$(shell pkg-config --cflags QtGui)
LIBS=$(shell pkg-config --libs QtGui)
CXXFLAGS=-g -MD -MP -W -Wall -pedantic -std=c++11 $(HEADERS)


all:
	$(MAKE) run_unit_tests
	$(MAKE) stacknew

stacknew: main.o qtuserinterface.o controller.o datestring.o \
  decodedhtmlstring.o makelistentries.o replacedstring.o \
  qtuserinterface_moc.o escapedtags.o realsystem.o userinterface.o \
  textfile.o
	$(CXX) -o $@ $^ -lPocoNet -lPocoFoundation -ljsoncpp $(LIBS)

run_unit_tests: \
  decodedhtmlstring_test.pass \
  textfile_test.pass \
  makelistentries_test.pass \
  escapedtags_test.pass \
  controller_test.pass
	

decodedhtmlstring_test: \
  decodedhtmlstring_test.o decodedhtmlstring.o replacedstring.o
	$(CXX) -o $@ $^

textfile_test: textfile_test.o textfile.o
	$(CXX) -o $@ $^

makelistentries_test: makelistentries_test.o makelistentries.o \
  decodedhtmlstring.o replacedstring.o datestring.o
	$(CXX) -o $@ $^

escapedtags_test: escapedtags_test.o escapedtags.o replacedstring.o
	$(CXX) -o $@ $^

controller_test: controller_test.o controller.o makelistentries.o \
  decodedhtmlstring.o userinterface.o replacedstring.o datestring.o
	$(CXX) -o $@ $^

%.pass: %
	./$^
	touch $@

%_moc.cpp: %.hpp
	moc-qt4 $^ >$@

clean:
	rm -f *.o *.d *_moc.cpp

-include *.d
