CXXFLAGS = -Wall -g -Iinclude
CXX=g++

src = $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)

TicTacToe: $(obj)
	$(CXX) -o $@ $^

.PHONY: clean

clean:
	rm -f src/*.o
