OBJS = main.o backend.o
BINARY = programa
CFLAGS = -pedantic -std=c99 -Wall -fsanitize=address -g
LSFLAGS = -fsanitize=address

all: programa

programa: $(OBJS)
	gcc $(LSFLAGS) -o $(BINARY) $(OBJS)
  
main2.o: main2.c ciudadADT.h
	gcc $(CFLAGS) -c main.c
  
backend.o: backend.c ciudadADT.h
	gcc $(CFLAGS) -c backend.c

clean:
	rm -f $(BINARY) $(OBJS)
