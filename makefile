main: path.o llist.o
	gcc -o main path.o llist.o

path.o: path.c path.h llist.h
	gcc -g -c path.c

llist.o: llist.c llist.h
	gcc -g -c llist.c

vector.o: vector.c
	gcc -g -o vector.o vector.c

clean:
	rm *.o
