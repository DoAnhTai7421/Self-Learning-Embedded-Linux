.PHONY: all clean

LIB_NAME := astatine_test

CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
INC_DIR := $(CUR_DIR)/inc
SRC_DIR := $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/objs

LIB_DIR := $(CUR_DIR)/libs
SHARED_LIB := $(LIB_DIR)/shared
STATIC_LIB := $(LIB_DIR)/static

INC_FLAGS := -I $(INC_DIR)

CC := gcc

mk_objs:
	$(CC) -c $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o $(INC_FLAGS)
	$(CC) -c -fPIC $(SRC_DIR)/print_text.c -o $(OBJ_DIR)/print_text.o $(INC_FLAGS)
	$(CC) -c -fPIC $(SRC_DIR)/calculate.c -o $(OBJ_DIR)/calculate.o $(INC_FLAGS)

mk_shared_libs:
	$(CC) -shared $(OBJ_DIR)/print_text.o $(OBJ_DIR)/calculate.o -o $(SHARED_LIB)/lib$(LIB_NAME).so

install:  
	cp -f $(SHARED_LIB)/lib$(LIB_NAME).so /usr/lib

all: mk_objs mk_shared_libs install
	$(CC) $(OBJ_DIR)/main.o -L$(SHARED_LIB) -l$(LIB_NAME) -o $(BIN_DIR)/use-shared-library

clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(SHARED_LIB)/lib$(LIB_NAME).so
	rm -rf $(BIN_DIR)/use-shared-library
