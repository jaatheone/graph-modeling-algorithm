#include "game_graph.h"


gameMatrix::gameMatrix(const string& filename)
{
	ifstream in (filename);
	string line;
	istringstream iss;
	int rows = 0;
	int columns = 0;
	int rows2 = 0;
	int columns2 = 0;

	if (!in.is_open())
	{
		std::cout << "Error opening file." << std::endl;
		return;
	}
	else
	{
		getline(in, line);
		iss.str(line);
		iss >> rows;
		iss >> columns;
		this->setRows(rows - 1);
		this->setColumns(columns - 1);
		getline(in, line);
		iss.str(std::string());
		iss.clear();
		iss.str(line);
		iss >> rows2;
		iss >> columns2;
		this->UpdateTarzanRow(rows2);
		this->UpdateTarzanColumn(columns2);
	}

	//getting first and second line

	matris = new matrix();

	//while loop to read entire game table to turn it into a graph
	for (int i = 0; i < rows; i++)
	{
		string temp = "?";
		getline(in, line);
		iss.str(std::string());
		iss.clear();
		iss.str(line);
		if (line.size() == 0) { continue; }
		std::vector<vertex_t*>row;
		matris->push_back(row);
		for (int j = 0; j < columns; j++)
		{
			iss >> temp;
			//if mark of node is X it means that there is no node therefore we do not need to waste space and time and just add a nullptr at that specific part of the table
			if (temp == "X")
			{
				vertex_t* temp = NULL;
				matris->at(i).push_back(temp);
			}
			//if the mark of the node is not X then we create a pointer to a vertex, save its x and y coordinates and its orientation or direction and then add it to the matris
			else 
			{
				vertex_t* v = new vertex();
				v->row = i;
				v->column = j;
				v->direction = setDirection(temp); 
				matris->at(i).push_back(v);
			}
		}
	}

	in.close();
}

void gameMatrix::getNeighbors(vertex_t* &v)
{
	//remember that the only possible moves a vertex has is moving 3 or 4 spaces in the direction of its orientation mark
	//therefore each vertex has 2 neighbors at most
	rumbo_t direction = v->direction;
	if (direction == rumbo_t::X)
	{
		return;
	}
	//passed node point North
	else if (direction == rumbo_t::N)
	{
		if (v->row - 3 >= 0)
		{
			//add neighbor with edge weight of 3
			if (matris->at(v->row - 3).at(v->column) != NULL)
			{
				v->neighbors_row.push_back(v->row - 3);
				v->neighbors_column.push_back(v->column);
				v->neighbors_distance.push_back(3);
			}
		}
		if (v->row - 4 >= 0)
		{
			//adds neighbor with edge weight of 4
			if (matris->at(v->row - 4).at(v->column) != NULL)
			{
				v->neighbors_row.push_back(v->row - 4);
				v->neighbors_column.push_back(v->column);
				v->neighbors_distance.push_back(4);
			}
			return;
		}
	}
	//passed node points North-West
	else if (direction == rumbo_t::NW)
	{
		if ((v->row - 3 >= 0) && (v->column - 3 >= 0))
		{
			//add neighbor with edge weight of 3
			if (matris->at(v->row - 3).at(v->column - 3) != NULL)
			{
				v->neighbors_row.push_back(v->row - 3);
				v->neighbors_column.push_back(v->column - 3);
				v->neighbors_distance.push_back(3);
			}
		}

		if ((v->row - 4 >= 0) && (v->column - 4 >= 0))
		{
			//adds neighbor with edge weight of 4
			if (matris->at(v->row - 4).at(v->column - 4) != NULL)
			{
				v->neighbors_row.push_back(v->row - 4);
				v->neighbors_column.push_back(v->column - 4);
				v->neighbors_distance.push_back(4);
			}
			return;
		}
	}
	//passed node points North-West
	else if (direction == rumbo_t::NE)
	{
		if ((v->row - 3 >= 0) && (v->column + 3 <= this->graph_column))
		{
			//add neighbor with edge weight of 3
			if (matris->at(v->row - 3).at(v->column + 3) != NULL)
			{
				v->neighbors_row.push_back(v->row - 3);
				v->neighbors_column.push_back(v->column + 3);
				v->neighbors_distance.push_back(3);
			}
		}
		if ((v->row - 4 >= 0) && (v->column + 4 <= this->graph_column))
		{
			//adds neighbor with edge weight of 4
			if (matris->at(v->row - 4).at(v->column + 4) != NULL)
			{
				v->neighbors_row.push_back(v->row - 4);
				v->neighbors_column.push_back(v->column + 4);
				v->neighbors_distance.push_back(4);
			}
			return;
		}
	}
	//passed node points South
	else if (direction == rumbo_t::S)
	{
		if (v->row + 3 <= this->graph_row)
		{
			//add neighbor with edge weight of 3
			if (matris->at(v->row + 3).at(v->column) != NULL)
			{
				v->neighbors_row.push_back(v->row + 3);
				v->neighbors_column.push_back(v->column);
				v->neighbors_distance.push_back(3);
			}
		}
		if (v->row + 4 <= this->graph_row)
		{
			//adds neighbor with edge weight of 4
			if (matris->at(v->row + 4).at(v->column) != NULL)
			{
				v->neighbors_row.push_back(v->row + 4);
				v->neighbors_column.push_back(v->column);
				v->neighbors_distance.push_back(4);
			}
			return;
		}
	}
	//passed node points South-West
	else if (direction == rumbo_t::SW)
	{
		if ((v->row + 3 <= this->graph_row) && (v->column - 3 >= 0))
		{
			//add neighbor with edge weight of 3
			if (matris->at(v->row + 3).at(v->column - 3) != NULL)
			{
				v->neighbors_row.push_back(v->row + 3);
				v->neighbors_column.push_back(v->column - 3);
				v->neighbors_distance.push_back(3);
			}
		}
		if ((v->row + 4 <= this->graph_row) && (v->column - 4 >= 0))
		{
			//adds neighbor with edge weight of 4
			if (matris->at(v->row + 4).at(v->column - 4) != NULL)
			{
				v->neighbors_row.push_back(v->row + 4);
				v->neighbors_column.push_back(v->column - 4);
				v->neighbors_distance.push_back(4);
			}
			return;
		}
	}
	//passed node points South-East
	else if (direction == rumbo_t::SE)
	{
		if ((v->row + 3 <= this->graph_row) && (v->column + 3 <= this->graph_column))
		{
			//add neighbor with edge weight of 3
			if (matris->at(v->row + 3).at(v->column + 3) != NULL)
			{
				v->neighbors_row.push_back(v->row + 3);
				v->neighbors_column.push_back(v->column + 3);
				v->neighbors_distance.push_back(3);
			}
		}
		if ((v->row + 4 <= this->graph_row) && (v->column + 4 <= this->graph_column))
		{
			//adds neighbor with edge weight of 4
			if (matris->at(v->row + 4).at(v->column + 4) != NULL)
			{
				v->neighbors_row.push_back(v->row + 4);
				v->neighbors_column.push_back(v->column + 4);
				v->neighbors_distance.push_back(4);
			}
			return;
		}
	}
	//passed node points to West
	else if (direction == rumbo_t::W)
	{
		if (v->column - 3 >= 0)
		{
			//add neighbor with edge weight of 3
			if (matris->at(v->row).at(v->column - 3) != NULL)
			{
				v->neighbors_row.push_back(v->row);
				v->neighbors_column.push_back(v->column - 3);
				v->neighbors_distance.push_back(3);
			}
		}
		if (v->column - 4 >= 0)
		{
			//adds neighbor with edge weight of 4
			if (matris->at(v->row).at(v->column - 4) != NULL)
			{
				v->neighbors_row.push_back(v->row);
				v->neighbors_column.push_back(v->column - 4);
				v->neighbors_distance.push_back(4);
			}
			return;
		}
	}
	//passed node points to East
	else if (direction == rumbo_t::E)
	{
		if (v->column + 3 <= this->graph_column)
		{
			//add neighbor with edge weight of 3
			if (matris->at(v->row).at(v->column + 3) != NULL)
			{
				v->neighbors_row.push_back(v->row);
				v->neighbors_column.push_back(v->column + 3);
				v->neighbors_distance.push_back(3);
			}
		}
		if (v->column + 4 <= this->graph_column)
		{
			//adds neighbor with edge weight of 4
			if (matris->at(v->row).at(v->column + 4) != NULL)
			{
				v->neighbors_row.push_back(v->row);
				v->neighbors_column.push_back(v->column + 4);
				v->neighbors_distance.push_back(4);
			}
			return;
		}
	}
}

/*
int gameMatrix::getTarzanRow()
{
	int temp = tarzan_row;
	return temp;
}
int gameMatrix::getTarzanColumn()
{
	int temp = tarzan_column;
	return temp;
}
*/

void gameMatrix::findJojoDFS()
{
	std::vector<std::string> solucion_str; //keeps the direction of the move
	std::vector<int> solucion_int;  //keeps the distance of the move (either 3 or 4)
	std::vector<std::string> combined_solution; //vector to combine solucion_str and solucion_int after finding jojo

	vertex_t* curr = matris->at(tarzan_row - 1).at(tarzan_column - 1); //curr starts at tarzan location
	curr->mark = mark_t::DISCOVERED;
	vertex_t* prev = nullptr;
	vertex_t* target = nullptr;

	findJojoDFSRec(solucion_str, solucion_int, curr, prev, target);
	toFile(this->str, this->integral);
}

void gameMatrix::findJojoDFSRec(std::vector<std::string>& solucion_str, std::vector<int>& solucion_int, vertex_t* cur, vertex_t* prev, vertex_t* &target)
{
		prev = cur;
		getNeighbors(prev);
		vertex_t* vecino;
		for (unsigned int i = 0; i < prev->neighbors_row.size(); i++)
		{
			std::string direction;
			int distance = 0;
			vecino = matris->at(prev->neighbors_row.at(i)).at(prev->neighbors_column.at(i));
			if(vecino->direction == rumbo_t::J)
			{
				target = vecino;
				solucion_str.push_back(getDirection(prev));
				solucion_int.push_back(prev->neighbors_distance.at(i));
				setStr(solucion_str);
				setInt(solucion_int);
				solucion_str.push_back(getDirection(vecino));
				return;
			}
			if (vecino->mark != mark_t::DISCOVERED)
			{
				cur = vecino;
				setDiscovery(cur);
				solucion_str.push_back(getDirection(prev));
				solucion_int.push_back(prev->neighbors_distance.at(i));
				findJojoDFSRec(solucion_str, solucion_int, cur, prev, target);
				
				if (target != NULL)
				{
					return;
				}

				if (solucion_str.back() != "J" || target == NULL)
				{
					direction = solucion_str.back();
					solucion_str.pop_back();
					distance = solucion_int.back();
					solucion_int.pop_back();
				}

				//FIX MEEEEEE
			}
		}
}


string gameMatrix::getDirection(vertex_t* v)
{
	switch (v->direction)
	{
		case rumbo_t::N: return "N";
		case rumbo_t::NW: return "NW";
		case rumbo_t::NE: return "NE";
		case rumbo_t::S: return "S";
		case rumbo_t::SW: return "SW";
		case rumbo_t::SE: return "SE";
		case rumbo_t::E: return "E";
		case rumbo_t::W: return "W";
		case rumbo_t::J: return "J";
	}
}

rumbo_t gameMatrix::setDirection(string donde)
{
	if (donde == "N") {	return rumbo_t::N; }
	else if (donde == "S") { return rumbo_t::S; }
	else if (donde == "SW") { return rumbo_t::SW; }
	else if (donde == "SE") { return rumbo_t::SE; }
	else if (donde == "NW") { return rumbo_t::NW; }
	else if (donde == "NE") { return rumbo_t::NE; }
	else if (donde == "W") { return rumbo_t::W; }
	else if (donde == "E") { return rumbo_t::E; }
	else if (donde == "J") { return rumbo_t::J; }
}

void gameMatrix::setDiscovery(vertex_t*& t)
{
	t->mark = mark_t::DISCOVERED;
}

void gameMatrix::setRows(int r)
{
	this->graph_row = r;
}

void gameMatrix::setColumns(int c)
{
	this->graph_column = c;
}

void gameMatrix::toFile(vector<string> str, vector<int> numeros)
{
	string filename = "output.txt";
	fstream file_out;

	file_out.open(filename, std::ios_base::out);
	if (!file_out.is_open()) {
		cout << "failed to open " << filename << '\n';
	}
	else {
		for(unsigned int i = 0; i < str.size(); i++)
		{
			file_out << str[i] << "-" << numeros[i] << " ";
		}
		file_out << endl;
	}
}
