
BIN_DIR := ../bin
OBJ_DIR := ../obj

$(OBJ_DIR)/main.o: main.cpp
	mkdir -p $(OBJ_DIR)
	g++ -std=c++20 -c main.cpp -o $(OBJ_DIR)/main.o

$(BIN_DIR)/gun-tactyx: $(OBJ_DIR)/main.o
	mkdir -p ../bin
	g++ $(OBJ_DIR)/main.o /usr/lib/raylib/libraylib.a -lzip -lGL -lm -lpthread -ldl -lrt -lX11 -o $(BIN_DIR)/gun-tactyx

build: $(BIN_DIR)/gun-tactyx
	echo "Build Done"

run: build
	$(BIN_DIR)/gun-tactyx

clean:
	mkdir -p $(OBJ_DIR)
	rm -rf $(OBJ_DIR)/*
	mkdir -p $(BIN_DIR)
	rm -rf $(BIN_DIR)/*
