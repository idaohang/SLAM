llist.o: llist.c llist.h
	gcc -g -o llist.o llist.c llist.h

path.o: path.c path.h
	gcc -g -o path.o path.c path.h

vector.o: vector.c
	gcc -g -o vector.o vector.c

clean:
	rm vector
