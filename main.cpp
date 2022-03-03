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
#include<cmath>

bool parseLine(string &line, string &movieName, double &movieRating);

class ratingOrg {
  public:
    bool operator()(const string& a, const string& b) {
      if(stod(a.substr(a.find_last_of(",") + 1)) - stod(b.substr(b.find_last_of(",") + 1)) < 0.001) {
        if(abs(stod(a.substr(a.find_last_of(",") + 1)) - stod(b.substr(b.find_last_of(",") + 1))) < 0.001) {
          if(a.compare(b) > 0)
            return true;
          else 
            return false;
        }
        return true;
      }
      return false;
    }
};

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
  ss << movieName << ", " << setprecision(2) << movieRating;
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
for(int i = 2; i < argc; i++) {
  priority_queue<string, vector<string>, ratingOrg> pq;
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
  cout << "Best movie with prefix "<< argv[i+2]<<" is: " << bestMovies.at(i).substr(0, bestMovies.at(i).find_last_of(",")) <<" with rating " << std::fixed << std::setprecision(1) << bestMovies.at(i).substr(bestMovies.at(i).find_last_of(",") + 1)<< endl;
}
    


return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/



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