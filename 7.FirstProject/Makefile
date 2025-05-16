CUR_DIR := .
INC_DIR := $(CUR_DIR)/inc
SRC_DIR := $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/obj
BIN_DIR := $(CUR_DIR)/bin
LIB_DIR := $(CUR_DIR)/lib

All:
	gcc -c -o $(OBJ_DIR)/main.o $(SRC_DIR)/main.c -I $(CUR_DIR)
	gcc -o app $(OBJ_DIR)/main.o -I $(CUR_DIR)
clean:
	rm -rf $(OBJ_DIR)/*.o app
	