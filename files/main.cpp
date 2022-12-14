#include "game_graph.h"
#include <exception>

using namespace std;
int main()
{
	string filename = "????";
	cout << "Please write the name of the file that you want to read from: " << endl;
	getline(cin, filename);
	gameMatrix* juego = new gameMatrix(filename);

	try
	{
		juego->findJojoDFS();
	}
	catch (exception& ex)
	{
		cout << "No solution could be found." << endl;
	}
	cout << "Done!" << endl;

	return 0;
}