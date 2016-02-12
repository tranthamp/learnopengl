CC=g++
LIBS=-lglfw3 -lglew -framework OpenGL
BIN=./bin
SRC=./src

PROGS=\
    hellowindow \
    hellotriangle \
    hellotriangle_ebo \
    hellotriangle_ex1

OUTPUT=$(addprefix $(BIN)/, $(PROGS))

all: $(BIN) $(OUTPUT)
.PHONY: clean

$(BIN):
	mkdir -p $(BIN)

$(BIN)/%: $(SRC)/%.cpp
	$(CC) $< -o $@ $(LIBS)

clean:
	rm $(BIN)/*
