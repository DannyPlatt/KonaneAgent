# Author: ChatGPT 3.5
# Last edited: 10/03/24 (DD/MM/YY)

# Define compiler and flags
CXX := g++
CXXFLAGS := -Wall

# Define source files
SRCS := KonaneBoard.cpp main.cpp MiniMaxPlayer.cpp MiniMaxPlayer2.cpp

# Define object files
OBJS := $(SRCS:.cpp=.o)

# Main target
prog: $(OBJS)
	$(CXX) $(OBJS) -o $@

# Rule to compile .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target to run the program
run: prog
	./prog

# Target to run tests
test: testKonaneBoard.cpp KonaneBoard.o
	$(CXX) $(CXXFLAGS) $^ -o $@
	./$@

# Target to clean up object files and executables
clean:
	rm -f $(OBJS) prog test

