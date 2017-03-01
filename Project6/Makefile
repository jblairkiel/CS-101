OBJs =  DGraph.o main.o

main: $(OBJs)
	g++ -Wall -std=c++11 -g $(OBJs) -o djikstra

#extra: $(OBJs)
# 	g++ -Wall -std=c++11 -g extra.cpp -o extra

#Queue.o: Queue.c Queue.h Stack.h
#	gcc -Wall -g -c  Queue.c

DGraph.o: 
	g++ -Wall -std=c++11 -g -c DGraph.cpp

clean:
	rm -f *.o
	rm -fr heapsort.dSYM
	rm -f ./djikstra

run:	clean main
	./djikstra sample.txt
