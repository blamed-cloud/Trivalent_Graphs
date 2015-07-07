#include "Graph.hpp"
#include<queue>
#include<unordered_set>

using namespace std;

Graph::Graph(vector<vector<int> > el, const int s)
	:size(s)
{
	al = vector<vector<int> >(size);
	for(int i(0); i<size; i++){
		al[i] = vector<int>();
	}

	for(int i(0); i<el.size(); i++){
		if(el[i].size() == 2){
			int v1 = el[i][0];
			int v2 = el[i][1];
			al[v1].push_back(v2);
			al[v2].push_back(v1);
		}
	}
}

vector<int> Graph::connectedComponentSizes(){
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
	return sizes;
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
			for( int j = 0; i < am[i].size(); j++)
			{
				int color = edge_is_forced(i,j);
				
				if (color == -1)
				{
					contradiction == true;
				} 
				else if (color >= 2)
				{
					am[i][j] = color;
					am[j][i] = color;
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
				compute_colorings_recurse();
				am[row][col] = 1;
				am[col][row] = 1;
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
	unordered_set<int> possible_colors;
	if (am[v1][v2] > 1)
	{
		possible_colors.insert(am[v1][v2]);
	}
	else
	{
		possible_colors.insert(2);
		possible_colors.insert(3);
		possible_colors.insert(4);	
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
				colors_both.insert(am[v1][j]);
			}
		}
	}
	
	if (colors_v1.size() == 2)
	{
		for(int c : colors_v1)
		{
			unordered_set<int>::iterator iter = possible_colors.find(c);
			if (iter != possible_colors.end())
			{
				possible_colors.erase(iter);	
			}
		}
	}
	
	if (colors_v2.size() == 2)
	{
		for(int c : colors_v2)
		{
			unordered_set<int>::iterator iter = possible_colors.find(c);
			if (iter != possible_colors.end())
			{
				possible_colors.erase(iter);	
			}
		}
	}
	
	if (colors_both.size() == 2)
	{
		for(int c : colors_both)
		{
			unordered_set<int>::iterator iter = possible_colors.find(c);
			if (iter != possible_colors.end())
			{
				possible_colors.erase(iter);	
			}
		}
	}
	
	if(possible_colors.size() == 0)
	{
		value = -1;
	}
	else if (possible_colors.size() == 1)
	{
		for( int c : possible_colors)
		{
			value = c;
		}
	}
	
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
