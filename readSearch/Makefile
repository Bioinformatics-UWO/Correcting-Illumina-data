
MAKE=make
CXX=g++ -O3 -Wall -fomit-frame-pointer -fopenmp

readSearch: readSearch.o divsufsort.o
	$(CXX) readSearch.o divsufsort.o -o $@
	
divsufsort.o : divsufsort.c divsufsort.h
	$(CXX) -c divsufsort.c -o $@

readSearch.o: readSearch.cpp divsufsort.h
	$(CXX) -c readSearch.cpp -o $@

clean:
	rm -f *.o
	rm -f readSearch