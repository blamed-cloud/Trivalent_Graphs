#ifndef GRAPH_H
#define GRAPH_H

#include<vector>
#include<iostream>

using namespace std; 

class Graph {
	
	public:
		Graph(vector< vector<int> > el, const int size);
		int isConnected();
		int getSize();

	private:
		void setConnectivity();
		void setPlanarity();
		void compute_colorings();
		void compute_colorings_recurse();
		int edge_is_forced(int v1, int v2);
		void print_am();

		vector<vector<int> > al;
		vector<vector<int> > am;
		vector<vector<int> > el;
		int connectivity;
		int is_circle_cross_prime;
		int is_connected;
		int is_planar;
		const int size;
		int signed_coloring_number;
		int number_of_three_colorings;
		
friend ostream& operator<<(ostream& os, const Graph g);
};

#endif
