#include "Graph.hpp"
#include "EdgelistFromString.hpp"
#include<string>
#include<vector>
#include<iostream>
#include<sstream>

int main(){
	stringstream ss;
	vector<vector<int> > v;
	int v1,v2,sz;

	cin >> sz;
	while((cin >> v1 >> v2)){
		ss << v1 << " " << v2 << "  ";
	}
	
	v = EdgelistFromString(ss.str(),sz);
	Graph g2(v,sz);

	cout << g2 << endl;
}
