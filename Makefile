CXX = g++

CXXFLAGS = -Wall -Wno-initialized -g

all: runMovies

runMovies: main.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

clean:
	/bin/rm -f runMovies *.o