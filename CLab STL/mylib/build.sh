#!/bin/bash

# Directories
SRC_DIR="src"
OBJ_DIR="obj"
LIB_DIR="lib"
INCLUDE_DIR="include"
TEST_DIR="test"

# Ensure object and library directories exist
mkdir -p $OBJ_DIR
mkdir -p $LIB_DIR

# Compile source files into object files
gcc -c $SRC_DIR/tree.c -o $OBJ_DIR/tree.o -I$INCLUDE_DIR
gcc -c $SRC_DIR/heap.c -o $OBJ_DIR/heap.o -I$INCLUDE_DIR
gcc -c $SRC_DIR/stack.c -o $OBJ_DIR/stack.o -I$INCLUDE_DIR
gcc -c $SRC_DIR/queue.c -o $OBJ_DIR/queue.o -I$INCLUDE_DIR
gcc -c $SRC_DIR/generic_ll.c -o $OBJ_DIR/generic_ll.o -I$INCLUDE_DIR
gcc -c $SRC_DIR/avl.c -o $OBJ_DIR/avl.o -I$INCLUDE_DIR

# Create the static library
ar rcs $LIB_DIR/libmylib.a $OBJ_DIR/tree.o $OBJ_DIR/heap.o $OBJ_DIR/stack.o $OBJ_DIR/queue.o $OBJ_DIR/generic_ll.o $OBJ_DIR/avl.o

# Compile the test program
gcc -o main $TEST_DIR/main.c -I$INCLUDE_DIR -L$LIB_DIR -lmylib

echo "Build completed!"
