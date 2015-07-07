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

		vector<vector<int> > al;
		vector<vector<int> > am;
		vector<vector<int> > el;
		int connectivity;
		int is_circle_cross_prime;
		int is_connected;
		int is_planar;
		const int size;
		
friend ostream& operator<<(ostream& os, const Graph g);
};

#endif
