CC := g++
CFLAGS := -Wall -Wextra -g -std=c++20

SRC := ./src
INCLUDE := ./include
BIN := ./bin
LIB := ./lib

EXECUTABLE := mift
LIBS := -lsfml-window -lsfml-graphics -lsfml-system

all: $(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CC) $(CFLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBS)

run: all
	$(BIN)/$(EXECUTABLE)

.PHONY: clean

clean:
	-rm $(BIN)/$(EXECUTABLE)
