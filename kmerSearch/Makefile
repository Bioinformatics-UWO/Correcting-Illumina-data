
MAKE=make
CXX=g++ -O3 -Wall -fomit-frame-pointer -fopenmp

kmerSearch: kmerSearch.cpp
	$(CXX) kmerSearch.cpp -o $@

clean:
	rm -f *.o
	rm -f kmerSearch
