CC = gcc
CFLAGS  = -g -Wall
default: program

program: program.o
	$(CC) $(CFLAGS) -o program program.o -lm

program.o: program.c
	$(CC) $(CFLAGS) -c program.c

clean:
	$(RM) program *.o *~
