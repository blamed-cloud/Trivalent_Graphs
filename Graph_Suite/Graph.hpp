#ifndef GRAPH_H
#define GRAPH_H

#include<vector>
#include<iostream>

using namespace std; 

class Graph {
	
	public:
		Graph(vector< vector<int> > el, const int size);
		bool isConnected();
		
		int getSize();

	private:
		vector<vector<int> > al;
		vector<vector<int> > am;
		const int size;
		
friend ostream& operator<<(ostream& os, const Graph g);
};

#endif
