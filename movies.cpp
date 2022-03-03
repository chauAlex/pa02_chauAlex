#include"movies.h"

bool ratingOrg::operator()(const string& a, const string& b) {
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