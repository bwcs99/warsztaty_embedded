CC=gcc
CFLAGS=-I.
DEPS = list.h
OBJ = list.o tests.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tests: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)