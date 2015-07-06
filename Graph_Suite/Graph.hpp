#ifndef GRAPH_H
#define GRAPH_H

#include<vector>
#include<iostream>

using namespace std; 

class Graph {
	
	public:
		Graph(vector< vector<int> > el, const int size);
		vector<int> connectedComponentSizes();
		
		int getSize();

	private:
		vector<vector<int> > al;
		const int size;
		
friend ostream& operator<<(ostream& os, const Graph g);
};

#endif
