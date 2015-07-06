#include "EdgelistFromString.hpp"
#include<iostream>

using namespace std;

vector<vector<int> > EdgelistFromString(string s, int size){
	vector<vector<int> > el;
	el.reserve(size);
	stringstream ss(s);
	int v1, v2;
	while( (ss >> v1) && (ss >> v2) ){
		vector<int> vi(2);
		vi[0] = v1;
		vi[1] = v2;
		el.push_back(vi);
	}
	return el;
}
