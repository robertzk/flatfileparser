CC = g++
CFLAGS = -I.
DEPS = csv_iterator.h parse.h
OBJ = parse.o csv_iterator.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

flatfileparser: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

