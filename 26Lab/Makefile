run: main.o queue.o merge.o
	gcc -o lab26 queue.o merge.o main.o

main.o: main.c queue.h merge.h
	gcc -c main.c

merge.o: merge.c merge.h
	gcc -c merge.c

queue.o: queue.c queue.h
	gcc -c queue.c

clean:
	rm -f *.o lab26
