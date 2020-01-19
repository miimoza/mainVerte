CC=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -Iinclude -g
SRC=src/main.cc src/card.cc src/game.cc src/deck.cc
BIN=MainVerte

all:
	$(CC) $(CXXFLAGS) $(SRC) -o $(BIN)

clean:
	$(RM) $(BIN)
