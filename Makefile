PROJNAME=circbuf
INCLUDEDIRS=-I./include 
LIBDIRS=
LIBS=
CFLAGS=-std=c11 -g -O2 -Wall -Werror -pedantic
CC=gcc

TEST_INCLUDEDIRS=$(INCLUDEDIRS) -I$(CXXTESTDIR)
TEST_LIBDIRS=$(LIBDIRS) -L./lib
TEST_LIBS=-l$(PROJNAME) $(LIBS) 
CPPFLAGS=-std=c++14 -g -O2 -Wall -Werror -pedantic
CPP=g++

default:
	$(CC) -c $(CFLAGS) $(INCLUDEDIRS) $(LIBDIRS) src/*.c $(LIBS)
	ar rcs lib/lib$(PROJNAME).a *.o
	rm *.o
test: default
	cxxtestgen --error-printer -o test/tests.cpp test/*.hpp
	$(CPP) $(CPPFLAGS) $(TEST_INCLUDEDIRS) $(TEST_LIBDIRS) -o test/tests.o test/tests.cpp $(TEST_LIBS)
	./test/tests.o
clean:
	rm -f lib/*.a
	rm -f *.o
	rm -f test/*.o test/tests.cpp
all:
	default
	test
