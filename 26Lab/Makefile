run: main.o queue.o
	gcc -o lab26 queue.o main.o

main.o: main.c queue.h
	gcc -c main.c

queue.o: queue.c queue.h
	gcc -c queue.c

clean:
	rm -f *.o lab26
