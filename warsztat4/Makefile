CC=gcc
CFLAGS=-I.
DEPS = my_memset.h
OBJ = my_memset.o measurments.o 

%.o: %.c $(DEPS)
	$(CC) -c -mavx -o $@ $< $(CFLAGS)

measurments: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)