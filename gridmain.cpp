#include "gridgraph.h"


int main()
{
	
	cout << "\nRunning Tests" << endl << endl;

	int rows = 10;
	int columns = 10;

	cout << "Number of rows (column size): " << rows << endl;
	cout << "Number of columns (row size): " << columns << endl << endl;

	gridgraph grid(rows, columns);

	grid.display_vertices();
	grid.display_as_grid();





	return 0;
}
