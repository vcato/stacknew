HEADERS=$(shell pkg-config --cflags QtGui)
LIBS=$(shell pkg-config --libs QtGui)
CXXFLAGS=-g -MD -MP -W -Wall -pedantic -std=c++11 $(HEADERS)


all:
	$(MAKE) run_unit_tests
	$(MAKE) stacknew

stacknew: main.o qtuserinterface.o controller.o datestring.o \
  decodedstring.o makelistentries.o replacedstring.o \
  qtuserinterface_moc.o escapedtags.o realsystem.o userinterface.o
	$(CXX) -o $@ $^ -lPocoNet -lPocoFoundation -ljsoncpp $(LIBS)

run_unit_tests: \
  decodedstring_test.pass \
  makelistentries_test.pass \
  escapedtags_test.pass \
  controller_test.pass
	

decodedstring_test: decodedstring_test.o decodedstring.o replacedstring.o
	$(CXX) -o $@ $^

makelistentries_test: makelistentries_test.o makelistentries.o \
  decodedstring.o replacedstring.o datestring.o
	$(CXX) -o $@ $^

escapedtags_test: escapedtags_test.o escapedtags.o replacedstring.o
	$(CXX) -o $@ $^

controller_test: controller_test.o controller.o makelistentries.o \
  decodedstring.o userinterface.o replacedstring.o datestring.o
	$(CXX) -o $@ $^

%.pass: %
	./$^
	touch $@

%_moc.cpp: %.hpp
	moc-qt4 $^ >$@

clean:
	rm -f *.o *.d *_moc.cpp

-include *.d
