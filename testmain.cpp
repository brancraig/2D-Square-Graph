//testmain.cpp

/* Brandon Craig | brandonjcraig00 "at" gmail "dot" com */

#include "gridgraph.h"
#include <cstring>



void ASSERT(string test_name, bool test_function) {cout << test_name << ": "; test_function ? cout << "PASSED\n" : cout << "FAILED\n";}

bool test_coordinate_bounds(const gridgraph<char> & grid);
bool test_vertex_coord_by_position(const gridgraph<char> & grid);
bool test_vertex_position_by_coord(const gridgraph<char> & grid);



int main()
{

	gridgraph<char> grid(5,5);
	ASSERT("Coordinates do not exceed bounds", test_coordinate_bounds(grid));
	ASSERT("Each position matches its correct set of coordinates", test_vertex_position_by_coord(grid));
	ASSERT("Each set of coordinates matches its correct position", test_vertex_coord_by_position(grid)); 	

	return 0;

}


bool test_vertex_position_by_coord(const gridgraph<char> & grid)
{
	bool passing = true;
	unsigned int length = grid.get_size();
	unsigned int row_length = grid.get_row_size();
	unsigned int column_length = grid.get_column_size();

	unsigned int test_position;

	for(unsigned int i = 0, counter = 0; i < row_length && passing; ++i)
	{
		for(unsigned int j = 0; j < column_length && passing; ++j, ++counter){

			passing = grid.get_position_by_coordinate(test_position, i, j);
			//cout << "EXPECTED: " << counter << ", FOUND: " << test_counter << '.' << endl;
			if(test_position != counter || counter > length)
				passing = false;

		}
	}

	return passing;	
}



bool test_vertex_coord_by_position(const gridgraph<char> & grid)
{
	bool passing = true;
	unsigned int length = grid.get_size();
	unsigned int row_length = grid.get_row_size();
	unsigned int column_length = grid.get_column_size();

	unsigned int test_position = 0;
	unsigned int test_row;
	unsigned int test_column;

	while(test_position < length && passing){

		for(unsigned int i = 0; i < row_length && passing; ++i)
		{
			for(unsigned int j = 0; j < column_length && passing; ++j, ++test_position){

				passing = grid.get_coordinate_by_position(test_position, test_row, test_column);
				//cout << "EXPECTED: (" << i << ", " << j << "), FOUND: (" << test_row << ", " << test_column << ")." << endl;
				if(test_row != i || test_column != j)
					passing = false;

			}
		}

	}
	return passing;	
}



bool test_coordinate_bounds(const gridgraph<char> & grid)
{
	bool passing = true;
	unsigned int length = grid.get_size();
	unsigned int row_length = grid.get_row_size();
	unsigned int column_length = grid.get_column_size();

	unsigned int test_row;
	unsigned int test_column;

	for(unsigned int position = 0; position < length && passing; ++position)
	{
		if(!grid.get_coordinate_by_position(position, test_row, test_column) 
				|| test_row < 0 || test_column < 0 || test_row > column_length || test_column > row_length)
			passing = false;
	}
	return passing;	

}

