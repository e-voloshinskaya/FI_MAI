compile: main.o table.o
	gcc -o kp9 main.o table.o

main.o: main.c
	gcc -c main.c

table.o: table.c table.h
	gcc -c table.c

clean:
	rm -f *.o kp9