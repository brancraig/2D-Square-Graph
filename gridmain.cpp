#include "gridgraph.h"


int main()
{
	

	int rows = 5;
	int columns = 5;

	cout << "Number of rows (column size): " << rows << endl;
	cout << "Number of columns (row size): " << columns << endl << endl;

	gridgraph<char> grid(rows, columns);

	grid.display_vertices();
	grid.display_as_grid();

	gridgraph<char> grid2(grid);
	grid2.display_vertices();
	grid2.display_as_grid();





	return 0;
}
