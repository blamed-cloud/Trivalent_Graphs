#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include "Graph_Suite/EdgelistFromString.hpp"
#include "Graph_Suite/Graph.hpp"

using namespace std;
int main(){

	string name;
	string el_string;
	int e1,e2;
	int v,e;
	while(getline(cin,name)){
		getline(cin,name);
		cout << name << endl;

		cin >> v >> e;
		//getline(cin,name);
		cin.ignore();

		cout << "v = " << v << ", e = " << e << endl;

		getline(cin,el_string);
		cout << el_string << endl;

		Graph g(EdgelistFromString(el_string,e),v);
		cout << g << endl;
	}
		
}
