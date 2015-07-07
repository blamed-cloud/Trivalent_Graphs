#include "Graph.hpp"
#include<queue>

using namespace std;

Graph::Graph(vector<vector<int> > el, const int s)
	:size(s)
{
	al = vector<vector<int> >(size);
	am = vector<vector<int> >(size);
	for(int i(0); i<size; i++){
		al[i] = vector<int>();
		am[i] = vector<int>(size);
		for(int j(0); j<size; j++){
			am[i][j] = 0;
		}
	}

	for(int i(0); i<el.size(); i++){
		if(el[i].size() == 2){
			int v1 = el[i][0];
			int v2 = el[i][1];
			al[v1].push_back(v2);
			al[v2].push_back(v1);
			am[v1][v2] = 1;
			am[v2][v1] = 1;
		}
	}
}



bool Graph::isConnected(){
	vector<int> flagged(size,0);
	queue<int> q;
	vector<int> sizes;

	for(int i(0); i < size; i++){
		if(!flagged[i]){
			int count(0);
			flagged[i]=1;
			q.push(i);
			count++;
			
			while(!q.empty()){
				int v = q.front();
				q.pop();
				for(int j(0); j < al[v].size(); j++){
					if(!flagged[al[v][j]]){
						flagged[al[v][j]]=1;
						q.push(al[v][j]);
						count++;
					}
					
				}
			}
			sizes.push_back(count);
		}
	}
	return (sizes.size()<2);
}


int Graph::getSize(){
	return size;
}


ostream& operator<<(ostream& os, const Graph g){
	for(vector<int> v:g.al){
		for(int e:v){
			os << e << " ";
		}
		os << "\n";
	}
	return os;
}
