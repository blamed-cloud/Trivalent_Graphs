#include "Graph.hpp"
#include<queue>
#include<unordered_set>
#include<algorithm>

using namespace std;

Graph::Graph(vector<vector<int> > el, const int s)
	: size(s)
	, el(el)
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

void Graph::setConnectivity(){
	int flag = 0;

	connectivity = 0;
	is_circle_cross_prime = -1;

	if( (connectivity = isConnected()) == 1){
		for(int i(0); i<el.size(); i++){
			for(int j(i+1); j<el.size(); j++){
				int v11 = el[i][0];
				int v12 = el[i][1];

				int v21 = el[j][0];
				int v22 = el[j][1];

				al[v11].erase( remove( al[v11].begin(), al[v11].end(), v12), al[v11].end() );
				al[v12].erase( remove( al[v12].begin(), al[v12].end(), v11), al[v12].end() );

				al[v21].erase( remove( al[v21].begin(), al[v21].end(), v22), al[v21].end() );
				al[v22].erase( remove( al[v22].begin(), al[v22].end(), v21), al[v22].end() );

				flag = (flag || (!isConnected()));

				al[v11].push_back(v12);
				al[v12].push_back(v11);

				al[v21].push_back(v22);
				al[v22].push_back(v21);
			}
		}
		if( !flag ){
			connectivity = 3;
		}
		else {
			connectivity = 2;
		}
	} 
	else if( connectivity == 3 ){

		flag = 0;
		is_circle_cross_prime = 0;

		for(int i(0); i<el.size(); i++){
			for(int j(i+1); j<el.size(); j++){
				for(int k(j+1); k<el.size(); k++){
					int v11 = el[i][0];
					int v12 = el[i][1];

					int v21 = el[j][0];
					int v22 = el[j][1];

					int v31 = el[k][0];
					int v32 = el[k][1];

					al[v11].erase( remove( al[v11].begin(), al[v11].end(), v12), al[v11].end() );
					al[v12].erase( remove( al[v12].begin(), al[v12].end(), v11), al[v12].end() );
					al[v21].erase( remove( al[v21].begin(), al[v21].end(), v22), al[v21].end() );
					al[v22].erase( remove( al[v22].begin(), al[v22].end(), v21), al[v22].end() );
					al[v31].erase( remove( al[v31].begin(), al[v31].end(), v32), al[v31].end() );
					al[v32].erase( remove( al[v32].begin(), al[v32].end(), v31), al[v32].end() );

					unordered_set<int> vs;
					
					vs.insert(v11);
					vs.insert(v12);
					vs.insert(v21);
					vs.insert(v22);
					vs.insert(v31);
					vs.insert(v32);

					flag = (flag || ((!isConnected()) && (vs.size()==6)) );

					al[v11].push_back(v12);
					al[v12].push_back(v11);

					al[v21].push_back(v22);
					al[v22].push_back(v21);

					al[v31].push_back(v32);
					al[v32].push_back(v31);
				}
			}
		}
		if( !flag ){
			is_circle_cross_prime = 1;
		}
	}
}

int Graph::isConnected(){
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
