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
		vector<vector<int> > am;
		const int size;		
		int signed_coloring_number;
		int number_of_three_colorings;

		void compute_colorings();
		void compute_colorings_recurse();
		int edge_is_forced(int v1, int v2);
		
friend ostream& operator<<(ostream& os, const Graph g);
};

#endif
