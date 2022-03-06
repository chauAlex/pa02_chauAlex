// Winter'22
// Instructor: Diba Mirza
// Student name: 
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
using namespace std;

#include<sstream>

bool parseLine(string &line, string &movieName, double &movieRating);

#include "movies.h"

int main(int argc, char** argv){
  if(argc < 2){
    cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
    cerr << "Usage: " << argv[ 0 ] << " filename prefix1 prefix2 ... prefix n " << endl;
    exit(1);
  }


  ifstream movieFile (argv[1]);
 

  if (movieFile.fail()){
    cerr << "Could not open file " << argv[1];
    exit(1);
  }
  
//Create an object of a STL data-structure to store all the movies
set<string> movieSet;

string line, movieName;
double movieRating;
stringstream ss;
// Read each file and store the name and rating
while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
  // Use std::string movieName and double movieRating
  // to construct your Movie objects
  // cout << movieName << " has rating " << movieRating << endl;
  // insert elements into your data structure
  ss.precision(1);
  ss << fixed << movieName << ", " << movieRating;
  movieSet.insert(ss.str());
  ss.str(""); //wipes everything in the ss
}

movieFile.close();

if(argc == 2){
  //print all the movies in ascending alphabetical order of movie names
  set<string>::iterator it = movieSet.begin();
  while(it != movieSet.end()) {
    cout << *it << endl;
    it++;
  }
  return 0;
}

//Part 2:
//populate the max rating heap
vector<string> bestMovies;
priority_queue<string, vector<string>, ratingOrg> pq;
for(int i = 2; i < argc; i++) {
  string key = argv[i];
  set<string>::iterator it = movieSet.begin();
  while(it != movieSet.end()) {
    if(it->substr(0, key.size()) == key)
    {
      pq.push(*it);
    }
    it++;
  }
  //check current best recommendation OR if pq is empty and thus no movie found
  if(!pq.empty()) {
    bestMovies.push_back(pq.top());
  } else {
    cout <<"No movies found with prefix "<< argv[i] <<endl;
  }
  //now print out the heap
  while(!pq.empty()) {
    cout << pq.top() << endl;
    pq.pop();
  }

  cout << endl;
}

for(int i = 0; i < bestMovies.size(); i++) {
  cout << "Best movie with prefix "<< argv[i+2]<<" is: " << bestMovies.at(i).substr(0, bestMovies.at(i).find_last_of(",")) <<" with rating" << std::fixed << std::setprecision(1) << bestMovies.at(i).substr(bestMovies.at(i).find_last_of(",") + 1)<< endl;
}
    


return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/
/*
Beginning with the for loop on Line 73, this loop will execute m times, as it depends on the amount of prefix values
that are inputted by the user.
  I will use indentation to indicate operations that may happen within a loop, and I will expand on this later how this
  will be portrayed through the Big-O notation. Lines 74 and 75 are constant time as they are just the initialization of
  a string and an iterator. Line 76 begins a while loop that will execute n times, as it is checking through the movie set
  to see which movies match the same prefix.
    Each comparison made by the if statement on Line 77 is constant time, and the if statement evaluates to true a max
    of k times, the number of movies that have the given prefix. The operation of pushing into the heap made
    on Line 79 takes about O(log(j)) where j is the number of items currently stored in the heap. Thus, because this variable
    j increases from 1 to k throughout all of the iterations of this entire while loop, the true runtime of this while loop
    would be O(log(k!)) which we can approximate as O(klog(k)).
  Lines 84-88 are used to check if the heap is not empty, then to store the maximum rated value for each prefix as the best
  movie, which are all constant time operations that do not need to be considered in our Big-O.
  Lines 90-95 are used to empty out the heap and print them out from greatest to smallest rating of matching prefix movies,
  and thus it executes k times since it iterates and empties out the contents of the heap.
Finally, to print out all of the best movies the for loop on Lines 98-100 will execute m times at worst, meaning that all
the prefixes provided had movies in the set that did have a matching prefix.

Thus, in all:
O(m(nklog(k) + k) + m)
O(mnklog(k) + mk + m)
We can now discard the functions which may grow slower over time, and conclude:
O(mnklog(k))
*/
bool parseLine(string &line, string &movieName, double &movieRating) {
  if(line.length() <= 0) return false;
  string tempRating = "";

  bool flag = false;
  movieName = tempRating = "", movieRating = 0.0, flag = false;

  for (int i = 0; i < line.length(); i++){
    if(flag) tempRating += line[i];
    else if(line[i]==','&& line[0]!='"') flag = true;
    else {
		  if(i==0 && line[0]=='"') continue;
		  if(line[i]=='"'){ i++; flag=true; continue;}
		  movieName += line[i];
	  }
  }
  
  movieRating = stod(tempRating);
  return true;
}