
DEBUG = -g -DDEBUG
CFLAGS = -ansi -std=c99 -Wall $(DEBUG)

all: HandWriting

run:
	./HandWriting

clean:
	rm -f *.o
	rm -f HandWriting

HandWriting: top.o fileIO.o template.o
	gcc top.o fileIO.o template.o -o HandWriting -lm

top.o: top.c template.h
	gcc -c $(CFLAGS) top.c -o top.o

fileIO.o: fileIO.h fileIO.c
	gcc -c $(CFLAGS) fileIO.c -o fileIO.o

template.o: fileIO.h template.c
	gcc -c $(CFLAGS) template.c -o template.o
