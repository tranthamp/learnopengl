CC=g++
LIBS=-lglfw3 -lglew -framework OpenGL
BIN=./bin
SRC=./src

PROGS=$(patsubst $(SRC)/%.cpp,%,$(wildcard $(SRC)/*.cpp))
OUTPUT=$(addprefix $(BIN)/, $(PROGS))

all: $(BIN) $(OUTPUT)
.PHONY: clean

$(BIN):
	mkdir -p $(BIN)

$(BIN)/%: $(SRC)/%.cpp
	$(CC) $< -o $@ $(LIBS)

clean:
	rm $(BIN)/*
