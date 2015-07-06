#include "Graph.hpp"
#include "EdgelistFromString.hpp"
#include<string>
#include<vector>
#include<iostream>

int main(){
	string s = "0 1  1 2  3 4  4 5  6 7  6 8  6 9";
	const int size = 10;
	vector<vector<int> > v(size);
	
	v[0]=vector<int>(0);
	v[1]=vector<int>(0);
	v[2]=vector<int>(0);

	v[0].push_back(1);
	v[1].push_back(2);
	
	
	cout << v.size() << "\n";
	cout << v[0].size() << endl;
	cout << endl;

	for(int i(0); i<v.size(); i++){
		for(int j(0); j<v[i].size(); j++){
			cout << v[i][j] << " ";
		}
		cout << "\n";
	}
	cout << endl;
	
	v = EdgelistFromString(s,size);
	for(int i(0); i<v.size(); i++){
		for(int j(0); j<v[i].size(); j++){
			cout << v[i][j] << " ";
		}
		cout << "\n";
	}
	cout << endl;

	Graph g(v,size);
	
	cout << "\n" << g << endl;
	
	vector<int> sizes = g.connectedComponentSizes();
	
	cout << "sizes :" << endl;

	for(int e:sizes){
		cout << e << ", ";
	}
	cout << endl;
}
