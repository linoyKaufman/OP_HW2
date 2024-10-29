
CXX = g++
CXXFLAGS = -Wall -Wextra -g


all: mync tictactow


mync: mync.o main.o
	$(CXX) $(CXXFLAGS) -o mync mync.o main.o

tictactow: tictactow.o
	$(CXX) $(CXXFLAGS) -o tictactow tictactow.o

mync.o: mync.cpp
	$(CXX) $(CXXFLAGS) -c mync.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

tictactow.o: tictactow.cpp
	$(CXX) $(CXXFLAGS) -c tictactow.cpp

clean:
	rm -f *.o mync tictactow
