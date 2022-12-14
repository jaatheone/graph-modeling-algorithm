#ifndef __GAME_GRAPH_H
#define __GAME_GRAPH_H
#include <iostream>
#include <string>
#include <vector> 
#include <fstream>
#include <sstream>

using namespace std;

enum class mark_t { UNDISCOVERED = 0, DISCOVERED, EXPLORED };
enum class rumbo_t { N, S, E, W, NE, NW, SE, SW, X, J};

typedef struct vertex
{
	mark_t mark = mark_t::UNDISCOVERED; //marker to identify if the vertex has discovered or explored yet
	rumbo_t direction = rumbo_t::X; //marker to identify direction of vertex
	//std::vector<vertex_t*> neighbors;
	vector<int> neighbors_row;
	vector<int> neighbors_column;
	vector<int> neighbors_distance;
	int row = 0;
	int column = 0;

} vertex_t;

typedef std::vector <vector<vertex_t*>> matrix;

class gameMatrix
{
private:
	matrix* matris = NULL;
	//std::vector<vertex_t> vertices;
	int tarzan_row = 0;
	int tarzan_column = 0;
	int graph_row = 0;
	int graph_column = 0;
	vector<string> str;
	vector<int> integral;

public:
	gameMatrix(const string& filename);
	void getNeighbors(vertex_t* &v);
	//int getTarzanRow();
	//int getTarzanColumn();
	void findJojoDFS();
	void findJojoDFSRec(vector<string>&, vector<int>&, vertex_t*, vertex_t*, vertex_t*&);
	string getDirection(vertex_t*);
	rumbo_t setDirection(string donde);
	void UpdateTarzanRow(int row) { this->tarzan_row = row;  }
	void UpdateTarzanColumn(int column) { this->tarzan_column = column; }
	void setDiscovery(vertex_t*&);
	void setColumns(int);
	void setRows(int);
	void setStr(vector<string> str) { this->str = str; }
	void setInt(vector<int> numeros) { this->integral = numeros; }
	void toFile(vector<string>, vector<int>);

};

#endif
