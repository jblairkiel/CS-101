OBJs =  huffTree.o main.o

main: $(OBJs)
	g++ -Wall -std=c++11 -g $(OBJs) -o main 

#extra: $(OBJs)
# 	g++ -Wall -std=c++11 -g extra.cpp -o extra

#Queue.o: Queue.c Queue.h Stack.h
#	gcc -Wall -g -c  Queue.c

huffTree.o: 
	g++ -Wall -std=c++11 -g -c huffTree.cpp

clean:
	rm -f *.o
	rm -fr heapsort.dSYM
	rm -f ./main
	rm -f ./extra

run:	clean main
	./main sample.txt
