OBJs =  Hashtable.o main.o

tweets: $(OBJs)
	g++ -Wall -std=c++11 -g $(OBJs) -o project4

Mashtable.o: 
	g++ -Wall -std=c++11 -g -c Hashtable.cpp

clean:
	rm -f *.o
	rm -fr project4.dSYM
	rm -f ./project4

run:	clean tweets 
	./project4
