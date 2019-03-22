CC = gcc
COMPILER_FLAGS = -std=c99
LINKER_FLAGS = -lm
OBJ_NAME = siguel


all: main.o file_util.o
	$(CC) main.o file_util.o $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

main.o: main.c
	$(CC) -c main.c

file_util.o: file_util.c file_util.h
	$(CC) -c file_util.c