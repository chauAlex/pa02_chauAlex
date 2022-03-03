CXX = g++

CXXFLAGS = -Wall -Wno-uninitialized -Wno-sign-compare -g

all: runMovies

runMovies: main.o movies.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

clean:
	/bin/rm -f runMovies *.o