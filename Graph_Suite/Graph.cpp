#include "Graph.hpp"
#include<queue>
#include<unordered_set>
#include<algorithm>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/boyer_myrvold_planar_test.hpp>

using namespace std;

Graph::Graph(vector<vector<int> > el, const int s)
	: size(s)
	, el(el)
	, number_of_three_colorings(0)
	, signed_coloring_number(0)
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

	setConnectivity();
	setPlanarity();
	compute_colorings();
	//for(int i(0); i<am.size(); i++){
		//for(int j(0); j<am[i].size(); j++){
			//cout << am[i][j] ;
		//}
		//cout << endl;
	//}
}

void Graph::setPlanarity(){
	using namespace boost;

	typedef adjacency_list<vecS,
				vecS,
				undirectedS,
				property<vertex_index_t, int>
				> graph;

	graph g(size);

	for(int i(0); i<el.size(); i++){
		add_edge(el[i][0],el[i][1],g);
	}
	
	is_planar = boyer_myrvold_planarity_test(g);

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
	if( connectivity == 3 ){

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
		else {
			is_circle_cross_prime = 0;
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

void Graph::compute_colorings()
{
	int color = 2;
	for( int i = 0; i < am[0].size(); i++)
	{
		if (am[0][i] != 0)
		{
			am[0][i] = color;
			am[i][0] = color;
/*-------------------------------------*/
			//print_am();
/*-------------------------------------*/
			color++;
		}
	}
	compute_colorings_recurse();
	for( int i = 0; i < am.size(); i++)
	{
		for (int j = 0; j < am.size(); j++)
		{
			if (am[i][j] != 0)
			{
				am[i][j] = 1;
/*-------------------------------------*/
				//print_am();
/*-------------------------------------*/
			}
		}
	}
}

void Graph::compute_colorings_recurse()
{
	vector<vector<int> > change_list;
	bool changed = true;
	bool contradiction = false;
	bool fully_colored = true;
	while (!contradiction && changed)
	{
		changed = false;
		for( int i = 0; i < am.size(); i++)
		{
			for( int j = 0; j < am[i].size(); j++)
			{
				int color = edge_is_forced(i,j);
				
				if (color == -1)
				{
					contradiction = true;
				} 
				else if (color >= 2)
				{
					am[i][j] = color;
					am[j][i] = color;
/*-------------------------------------*/
					//print_am();
/*-------------------------------------*/
					vector<int> pair;
					pair.push_back(i);
					pair.push_back(j);
					change_list.push_back(pair);
					changed = true;
				}
			}
		}
	}
	
	if (!contradiction)
	{
		for( int i = 0; i < am.size(); i++)
		{
			for ( int j = 0; j < am[i].size(); j++)
			{
				if (am[i][j] == 1)
				{
					fully_colored = false;
				}
			}
		}
	} 
	else {
		fully_colored = false;
	}
	
	if (fully_colored)
	{
		number_of_three_colorings++;
		int sign_of_coloring = 1;
		for( int i = 0; i < am.size(); i++)
		{
			queue<int> colors;
			for( int j = 0; j < am.size(); j++)
			{
				if (am[i][j] != 0)
				{
					colors.push(am[i][j]);
				}
			}
			while (colors.front() != 2)
			{
				int temp = colors.front();
				colors.pop();
				colors.push(temp);
			}
			colors.pop();
			if (colors.front() == 4)
			{
				sign_of_coloring *= -1;
			}
		}
		signed_coloring_number += sign_of_coloring;
	}
	
	if (!contradiction && !fully_colored)
	{
		int row = 0;
		int col = 0;
		int color = 0;
		for( int i = 0; i < am.size(); i++)
		{
			int num = 0;
			int temp_color = 0;
			int temp_col = 0;
			for( int j = 0; j < am[i].size(); j++)
			{
				if (am[i][j] > 1)
				{
					num++;
					temp_color = am[i][j];
				} 
				else if (am[i][j] == 1)
				{	
					temp_col = j;
				}
			}
			if (num == 1)
			{
				row = i;
				col = temp_col;
				color = temp_color;
				break;
			}
		}
		vector<int> tried_colors = {1,1,0,0,0};
		tried_colors[color] = 1;
		for(int c = 2; c < tried_colors.size(); c++)
		{
			if (tried_colors[c] == 0)
			{
				am[row][col] = c;
				am[col][row] = c;
/*-------------------------------------*/
				//print_am();
/*-------------------------------------*/
				compute_colorings_recurse();
				am[row][col] = 1;
				am[col][row] = 1;
/*-------------------------------------*/
				//print_am();
/*-------------------------------------*/
				tried_colors[c] = 1;
			}
		}
	}
	
	//undo changes
	while (change_list.size() != 0)
	{
		vector<int> edge = change_list.back();
		change_list.pop_back();
		am[edge[0]][edge[1]] = 1;
		am[edge[1]][edge[0]] = 1;
/*-------------------------------------*/
		//print_am();
/*-------------------------------------*/
	}
}

int Graph::edge_is_forced(int v1, int v2)
{
	int value = 0;
	if (am[v1][v2] == 0)
	{
		return 0;
	}
	unordered_set<int> colors_v1;
	unordered_set<int> colors_v2;
	unordered_set<int> colors_both;
	vector<int> pc = {-1234,-1234,0,0,0};
	if (am[v1][v2] > 1)
	{
		pc[am[v1][v2]] = 1;
	}
	else
	{
		pc[2] = 1;
		pc[3] = 1;
		pc[4] = 1;
	}
	
	for( int j = 0; j < am[v1].size(); j++)
	{
		if (j != v2)
		{
			if (am[v1][j] > 1)
			{
				colors_v1.insert(am[v1][j]);
				colors_both.insert(am[v1][j]);
			}
		}
	}
	
	for(int j = 0; j < am[v2].size(); j++)
	{
		if (j != v1)
		{
			if (am[v2][j] > 1)
			{
				colors_v2.insert(am[v2][j]);
				colors_both.insert(am[v2][j]);
			}
		}
	}
	
	if (colors_v1.size() == 2)
	{
		for(int c : colors_v1)
		{
			pc[c] = 0;
		}
	}
	
	if (colors_v2.size() == 2)
	{
		for(int c : colors_v2)
		{
			pc[c] = 0;
		}
	}
	
	if (colors_both.size() >= 2)
	{
		for(int c : colors_both)
		{
			pc[c] = 0;
		}
	}
	
	if(!pc[2] && !pc[3] && !pc[4])
	{
		value = -1;
	}
	else if ((pc[2] + pc[3] + pc[4] ) == 1)
	{
		value = pc[2]*2 + pc[3]*3 + pc[4]*4;
	}
	
	if(value > 1 && value == am[v1][v2])
	{
		value = 0;
	}
	
	return value;
}

int Graph::getSize(){
	return size;
}

void Graph::print_am()
{
	for(int iii = 0; iii < am.size(); iii++)
	{
		for(int jjj = 0; jjj < am[iii].size(); jjj++)
		{
			cout << am[iii][jjj];
		}
		cout << endl;
	}
	cout << endl;
}


ostream& operator<<(ostream& os, const Graph g){
	os << "connectivity = " << g.connectivity << endl;
	os << "is_circle_cross_prime = " << g.is_circle_cross_prime << endl;
	os << "is_planar = " << g.is_planar << endl;
	os << "signed_coloring_number = " << g.signed_coloring_number << endl;
	os << "number_of_three_colorings = " << g.number_of_three_colorings << endl;
	return os;
}
