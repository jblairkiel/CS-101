OBJs =  myClock.o hats.o besideHats.o main.o

sticks: $(OBJs)
	g++ -Wall -std=c++11 -g $(OBJs) -o sticks 

#Queue.o: Queue.c Queue.h Stack.h
#	gcc -Wall -g -c  Queue.c

myClock.o: 
	g++ -Wall -std=c++11 -g -c myClock.cpp

hats.o:
	g++ -Wall -std=c++11 -g -c hats.cpp

besideHats.o:
	g++ -Wall -std=c++11 -g -c besideHats.cpp

clean:
	rm -f *.o
	rm -fr heapsort.dSYM

run:	clean sticks 
	./sticks
