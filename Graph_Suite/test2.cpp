#include "Graph.hpp"
#include "EdgelistFromString.hpp"
#include<string>
#include<vector>
#include<iostream>
#include<sstream>
#include<time.h>
#include<stdio.h>

int main(){
	stringstream ss;
	vector<vector<int> > v;
	int v1,v2,sz;

	cin >> sz;
	while((cin >> v1 >> v2)){
		ss << v1 << " " << v2 << "  ";
	}
	
	v = EdgelistFromString(ss.str(),sz);
	clock_t start = clock(), diff;
	Graph g2(v,sz);
	diff = clock() - start;

	int msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);

	cout << g2 << endl;
}
