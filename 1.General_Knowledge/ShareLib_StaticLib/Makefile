CUR_DIR := .
INC_DIR := $(CUR_DIR)/inc
SRC_DIR := $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/obj
BIN_DIR := $(CUR_DIR)/bin
LIB_DIR := $(CUR_DIR)/lib
LIB_STATIC_DIR := $(LIB_DIR)/static
LIB_SHARED_DIR := $(LIB_DIR)/shared

creat_obj:
	gcc -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o -I $(CUR_DIR)
	gcc -c -fPIC $(SRC_DIR)/myMath.c -o $(OBJ_DIR)/myMath.o -I $(INC_DIR)

creat_static:
	ar rcs $(LIB_STATIC_DIR)/libmymath.a $(OBJ_DIR)/main.o $(OBJ_DIR)/myMath.o

creat_shared:
	gcc -shared $(OBJ_DIR)/myMath.o -o $(LIB_SHARED_DIR)/libmymath.so

linking_shared:
	gcc $(OBJ_DIR)/main.o -L$(LIB_SHARED_DIR) -lmymath -o $(BIN_DIR)/use-shared-library

linking_static:
	gcc $(OBJ_DIR)/main.o -L$(LIB_STATIC_DIR) -lmymath -o $(BIN_DIR)/use-static-library

shared: creat_obj creat_shared linking_shared
	@echo "creat shared library done"

static: creat_obj creat_static linking_static
	@echo "creat static library done"

clean:
	rm -rf $(BIN_DIR)/use-shared-library $(OBJ_DIR)/*.o $(LIB_SHARED_DIR)/*.so
