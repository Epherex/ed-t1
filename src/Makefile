CC = gcc
COMPILER_FLAGS = -std=c99 -fstack-protector-all
LINKER_FLAGS = -lm
EXEC_NAME = siguel
OBJECTS = main.o geometry.o object.o file_util.o tree.o svg.o commands.o

all: $(EXEC_NAME)

$(EXEC_NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXEC_NAME)

main.o: main.c file_util.h object.h commands.h tree.h
	$(CC) -c main.c $(COMPILER_FLAGS)

geometry.o: geometry.c geometry.h object.h
	$(CC) -c geometry.c $(COMPILER_FLAGS)

object.o: object.c object.h
	$(CC) -c object.c $(COMPILER_FLAGS)

file_util.o: file_util.c file_util.h
	$(CC) -c file_util.c $(COMPILER_FLAGS)

tree.o: tree.c tree.h
	$(CC) -c tree.c $(COMPILER_FLAGS)

svg.o: svg.c svg.h object.h
	$(CC) -c svg.c $(COMPILER_FLAGS)

commands.o: commands.c commands.h file_util.h tree.h svg.h geometry.h object.h
	$(CC) -c commands.c $(COMPILER_FLAGS)

clean:
	rm -rf *.o
