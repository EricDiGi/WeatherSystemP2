CXX = g++
CXXFLAGS = -g -std=c++11 -Wall

SRCS = $(wildcard *.hpp)
OBJECTS = $(SRCS: .hpp=.o)

all: clean client

client: $(OBJECTS) main.cpp
		$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf *.dSYM
		$(RM) *.o *.gc* test/*.o core client