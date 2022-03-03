#ifndef movies_h
#define movies_h

#include<iostream>
#include<string>
#include<cmath>

using namespace std;

class ratingOrg {
  public:
    bool operator()(const string& a, const string& b);
};
#endif