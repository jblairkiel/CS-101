OBJs =  Hashtable.o main.o

project1: $(OBJs)
	g++ -Wall -std=c++11 -g $(OBJs) -o project1

Hashtable.o: Hashtable.cpp Hashtable.h
	g++ -Wall -std=c++11 -g -c Hashtable.cpp
#Queue.o: Queue.c Queue.h Stack.h
#	gcc -Wall -g -c  Queue.c

clean:
	rm -f *.o
	rm -fr heapsort.dSYM
	rm -f ./project1

run:	clean project1
	./project1
