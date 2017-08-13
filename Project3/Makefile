OBJs =  LinkedList.o solution.o

solution: $(OBJs)
	g++ -Wall -std=c++11 -g $(OBJs) -o solution 

LinkedList.o:
	g++ -Wall -std=c++11 -g -c LinkedList.cpp

clean:
	rm -f *.o
	rm -f ./solution

run:	clean solution 
	./solution
