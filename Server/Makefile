CXX = g++
CXXFLAGS = -g -std=c++11 -Wall

SRCS = $(wildcard *.hpp)
OBJECTS = $(SRCS: .hpp=.o)

all: clean server

server: $(OBJECTS) main.cpp service_thread.hpp glob.hpp location.hpp location.cpp action_handler.hpp action_handler.cpp
		$(CXX) $(CXXFLAGS) -o $@ $^ -pthread

clean:
	rm -rf *.dSYM
		$(RM) *.o *.gc* test/*.o core server