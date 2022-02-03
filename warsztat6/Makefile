CC=gcc
CFLAGS=-I.
DEPS = vector.h
OBJ = vector.o tests.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tests: $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS)