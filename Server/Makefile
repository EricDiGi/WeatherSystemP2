CXX = g++
CXXFLAGS = -g -std=c++11 -Wall

SRCS = $(wildcard *.hpp)
OBJECTS = $(SRCS: .hpp=.o)

all: clean server

server: $(OBJECTS) main.cpp service_thread.hpp
		$(CXX) $(CXXFLAGS) -o $@ $^ -pthread

clean:
	rm -rf *.dSYM
		$(RM) *.o *.gc* test/*.o core server