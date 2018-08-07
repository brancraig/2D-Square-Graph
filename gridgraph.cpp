//gridgraph.cpp

/* Brandon Craig | brandonjcraig00 "at" gmail "dot" com */

/* This is a graph for any N by M (N, M > 1) 2-dimensional square grid. In a square grid there
 * are corner, side, and center vertices. Here each one is treated as its own type derived from
 * an abstract base vertex class. This allows for easy tabulation of adjacency pointers across
 * the grid. In this version, diagonally-adjacent squares are NOT tabulated; only those directly
 * adjacent are kept. For example: corners have 2 adjacent vertices; sides have 3; centers have 4.*/


#include "gridgraph.h"

/* FUNCTION: Default constructor for the graph when no arguments are given.
 * ARGUMENTS: Uses global constants as parameters (Set in 'gridgraph.h') 
 * RETURN: Returns no values.
 */
gridgraph::gridgraph(int rows_in_grid, int columns_in_grid)
{
    row_size = columns_in_grid;
    column_size = rows_in_grid;
    graph_init();
}


/* FUNCTION: Constructor for the graph when the size of the grid (rows by columns) is given.
 * ARGUMENTS: the number of rows and the number of columns. 
 * RETURN: Returns no values.
 */
gridgraph::gridgraph(const unsigned int & rows_in_grid, const unsigned int & columns_in_grid)
{
    row_size = columns_in_grid;
    column_size = rows_in_grid;
    graph_init();
}


/* FUNCTION: Constructor for abstract base vertex.
 * ARGUMENTS: the position of the vertex along the array of vertices, and its position (x, y) in the grid.
 * RETURN: Returns no values.
 */
vertex::vertex(const unsigned int & pos, const unsigned int & x, const unsigned int & y)
{
    position = pos;
    row_pos = x;
    column_pos = y;
    visited = false;
}


/* FUNCTION: Constructor for a corner vertex.
 * ARGUMENTS: the position of the vertex along the array of vertices, and its position (x, y) in the grid.
 * RETURN: Returns no values.
 */
corner::corner(const unsigned int & array_position, const unsigned int & row_position, const unsigned int & column_position) : vertex(array_position, row_position, column_position)
{}


/* FUNCTION: Constructor for a side vertex.
 * ARGUMENTS: the position of the vertex along the array of vertices, and its position (x, y) in the grid.
 * RETURN: Returns no values.
 */
side::side(const unsigned int & array_position, const unsigned int & row_position, const unsigned int & column_position) : vertex(array_position, row_position, column_position)
{}


/* FUNCTION: Constructor for a center vertex.
 * ARGUMENTS: the position of the vertex along the array of vertices, and its position (x, y) in the grid.
 * RETURN: Returns no values.
 */
center::center(const unsigned int & array_position, const unsigned int & row_position, const unsigned int & column_position) : vertex(array_position, row_position, column_position)
{}



/* FUNCTION: Function initializes the graph by iterating through the vertices and deducing each vertex's type.
 * ARGUMENTS: None. Class members that are stored in the constructor act as parameters to this function. 
 * RETURN: Returns no values. 
 */
void gridgraph::graph_init()
{
    array_length = row_size * column_size;
    gridArray = new vertex*[array_length];
    END = (gridArray + array_length);

    vertex ** current = gridArray;
    unsigned int array_position = 0;
    for(unsigned int row = 0; row < column_size; ++row)
        for(unsigned int column = 0; column < row_size; ++column, ++array_position, ++current){
	    //cout << '(' << row << ", " << column  << ")\n";
            *current = determine_vertex_type(array_position, row, column);
	}

    current = gridArray;
    while(current < END)
    {
        (**current).create_adjacencies(row_size, column_size, gridArray);
        ++current;
    }
}


/* FUNCTION: Helps the "graph_init" function by doing the vertex type determination part of setting up the grid. 
 * ARGUMENTS: Take the "position" of the vertex in the array, and its position in its row and column. 
 * RETURN: Returns the pointer to the new vertex.
 */
vertex * gridgraph::determine_vertex_type(const unsigned int & position, const unsigned int & row_position, const unsigned int & column_position)
{
    unsigned int adjacencies = 4;
    
    //cout << position << " " << row_position << " " << row_size << " " << column_position << " " << column_size << endl;
    
    if(row_position == 0 || row_position == column_size - 1)
        --adjacencies;

    if(column_position == 0 || column_position == row_size - 1)
        --adjacencies;

    if(adjacencies == 3)
        return new side(position, row_position, column_position);

    if(adjacencies == 4)
        return new center(position, row_position, column_position);

    if(adjacencies == 2)
        return new corner(position, row_position, column_position);


    return NULL;
}



/* FUNCTION: Tabulates the adjacencies for the corner vertex type and stores them in that vertex.
 * ARGUMENTS: The size of the rows in the grid and the starting address of the vertex array from the gridgraph.
 * RETURN: Returns no values.
 */
void corner::create_adjacencies(const unsigned int & row_size, const unsigned int & column_size, vertex ** grid) 
{
	   	
   if(row_pos == 0){ //top
        if(column_pos == 0)         //left
        {
            vertical_adj = *(grid + position + row_size);
            horizontal_adj = *(grid + position + 1);
        } else {               //right
            vertical_adj = *(grid + position + row_size);
            horizontal_adj = *(grid + position - 1);
        }
   }else{       //bottom
       if(column_pos == 0)           //left
       {                   
           vertical_adj = *(grid + position - row_size);
           horizontal_adj = *(grid + position + 1);
       }else{                 //right
           vertical_adj = *(grid + position - row_size);
           horizontal_adj = *(grid + position - 1);
       }
   }
}

/* FUNCTION: Tabulates the adjacencies for the side vertex type and stores them in that vertex.
 * ARGUMENTS: The size of the rows in the grid and the starting address of the vertex array from the gridgraph.
 * RETURN: Returns no values.
 */
void side::create_adjacencies(const unsigned int & row_size, const unsigned int & column_size, vertex ** grid) 
{

    if(row_pos == 0) //top side
    {
        pi_radian1st = *(grid + position + 1); //top next right
        pi_radian2nd = *(grid + position - 1); //top next left
        pi_radian3rd = *(grid + position + row_size); //below this side
    }
    else if(column_pos == 0) //left side
    {
        pi_radian1st = *(grid + position + 1); //side next right
        pi_radian2nd = *(grid + position - row_size); //above this side
        pi_radian3rd = *(grid + position + row_size); //below this side

    }
    else if(row_pos == column_size - 1) // bottom side
    {
        pi_radian1st = *(grid + position + 1); //bottom next right
        pi_radian2nd = *(grid + position - row_size); //above this side
        pi_radian3rd = *(grid + position - 1); //bottom next left
    }
    else if(column_pos == row_size - 1) // right side; 
    {
        pi_radian1st = *(grid + position - row_size); //above this side
        pi_radian2nd = *(grid + position - 1); //left of this side
        pi_radian3rd = *(grid + position + row_size); //below this side
    }
    else{}
}



/* FUNCTION: Tabulates the adjacencies for the center vertex type and stores them in that vertex.
 * ARGUMENTS: The size of the rows in the grid and the starting address of the vertex array from the gridgraph.
 * RETURN: Returns no values.
 */
void center::create_adjacencies(const unsigned int & row_size, const unsigned int & column_size, vertex ** grid) 
{
    right = *(grid + position + 1);
    up = *(grid + position - row_size);
    left = *(grid + position - 1);
    down = *(grid + position + row_size);
}




/* FUNCTION: A setter for the "value" contained within a particular vertex.
 * ARGUMENTS: The value to be set.
 * RETURN: Returns void.
 */
void vertex::set_value(char value)
{
	character = value;
	return;
}


/* FUNCTION: A getter for whatever "value" is contained within a particular vertex. 
 * ARGUMENTS: No params.
 * RETURN: Returns the value of the thing stored within the vertex. 
 */
char vertex::get_value(void) const
{
	return character;
}



/* FUNCTION: A getter that returns the row position of a given vertex.
 * ARGUMENTS: No params. 
 * RETURN: The row position data member. 
 */
unsigned int vertex::get_row_pos(void) const
{
    return row_pos;
}


/* FUNCTION: A getter that returns the columnal position of a given vertex. 
 * ARGUMENTS: No params. 
 * RETURN: The colomn position data member. 
 */
unsigned int vertex::get_column_pos(void) const
{
    return column_pos;
}


/* FUNCTION: A getter that returns the position of the vertex in the array of vertices. 
 * ARGUMENTS: No params.
 * RETURN: The position data member. 
 */
unsigned int vertex::get_position(void) const
{
    return position;
}


/* FUNCTION: Destructor for the gridgraph class. Deletes all dynamically allocated memory.
 * ARGUMENTS: No params.
 * RETURN: Returns no values. 
 */
gridgraph::~gridgraph()
{
    vertex ** temp = gridArray;
    if(gridArray)
    {
        while(temp < END)
        {
            delete *temp;
            ++temp;
        }
        delete [] gridArray;
        gridArray = NULL;
    }
    row_size = 0;
    column_size = 0;
    array_length = 0;
    return;
}

/* FUNCTION: Destructor for the corner class. No dynamic memory.
 * ARGUMENTS: No params.
 * RETURN: Returns no values. 
 */
corner::~corner()
{}


/* FUNCTION: Destructor for the side class. No dynamic memory.
 * ARGUMENTS: No params.
 * RETURN: Returns no values. 
 */
side::~side()
{}


/* FUNCTION: Destructor for the center class. No dynamic memory.
 * ARGUMENTS: No params.
 * RETURN: Returns no values. 
 */
center::~center()
{}


/* FUNCTION: Destructor for the vertex abstract class. No dynamic memory.
 * ARGUMENTS: No params.
 * RETURN: Returns no values. 
 */
vertex::~vertex()
{}





/* FUNCTION: Function to display the entire graph as a simple grid.
 * ARGUMENTS: No params.
 * RETURN: Returns no values.  
 */
void gridgraph::display_as_grid(void) const
{
    cout << endl;
    vertex ** temp = gridArray;
    for(unsigned int i = 0; i < column_size; ++i)
    {
        for(unsigned int j = 0; j < row_size; ++j)
        {
	
	    cout << '(' << (*temp)->get_row_pos() << ", " << (*temp)->get_column_pos()	<< ')' << '\t';
            ++temp;
        }
        cout << endl << endl;
    }
    cout << endl;
    return;
}




/* FUNCTION: Displays the grid in graph-notation form.
 * ARGUMENTS: No params.
 * RETURN: Returns no values.
 */
void gridgraph::display_vertices(void) const
{
    vertex ** start = gridArray;
    while(start < END)
    {
        for(unsigned int i = 0; i < row_size; ++i, ++start){
            (*start)->display();
            cout << endl;
        }
    }
    cout << endl;
}




/* FUNCTION: Displays the array, row, and column position, adjacencies, and type, of a corner.
 * ARGUMENTS: No params.
 * RETURN: Returns no values.
 */
void corner::display()
{
	cout << position << '\t'
	     << "corner\t" << '(' << row_pos << ", " << column_pos << ')' << " -> " 
	     << "((" << vertical_adj->get_row_pos()   << ", " << vertical_adj->get_column_pos()   << ')'  << ", " 
	     << '('  << horizontal_adj->get_row_pos() << ", " << horizontal_adj->get_column_pos() << "))" << endl;
}


/* FUNCTION: Displays the array, row, and column position, adjacencies, and type, of a side.
 * ARGUMENTS: No params.
 * RETURN: Returns no values.
 */
void side::display()
{
	cout << position << '\t'
	     << "side\t" << '(' << row_pos << ", " << column_pos << ')' << " -> " 
	     << "((" << pi_radian1st->get_row_pos() << ", " << pi_radian1st->get_column_pos() << ')'  << ", " 
	     << '('  << pi_radian2nd->get_row_pos() << ", " << pi_radian2nd->get_column_pos() << ')'  << ", " 
	     << '('  << pi_radian3rd->get_row_pos() << ", " << pi_radian3rd->get_column_pos() << "))" << endl;
}

/* FUNCTION: Displays the array, row, and column position, adjacencies, and type, of a center.
 * ARGUMENTS: No params.
 * RETURN: Returns no values.
 */
void center::display()
{
    cout << position << '\t'
	 << "center\t" << '(' << row_pos << ", " << column_pos << ')' <<  " -> " 
	 << "((" << right->get_row_pos() << ", " << right->get_column_pos() << ')' << ", " 
	 << '('  << up->get_row_pos()    << ", " << up->get_column_pos()    << ')' << ", "
	 << '('  << left->get_row_pos()  << ", " << left->get_column_pos()  << ')' << ", "
	 << '('  << down->get_row_pos()  << ", " << down->get_column_pos()  << "))" << endl;
}



/* FUNCTION: An empty function "to be determined" by whatever algorithm is being implemented.
 * ARGUMENTS: Dependent on usage.
 * RETURN: Returns no values. 
 */
void vertex::expand(){}


/* FUNCTION: An empty function "to be determined" by whatever algorithm is being implemented.
 * ARGUMENTS: Dependent on usage.
 * RETURN: Returns no values. 
 */
void corner::expand(){
	horizontal_adj->expand();
	vertical_adj->expand();
}


/* FUNCTION: An empty function "to be determined" by whatever algorithm is being implemented.
 * ARGUMENTS: Dependent on usage.
 * RETURN: Returns no values. 
 */
void side::expand(){
	pi_radian1st->expand();
	pi_radian2nd->expand();
	pi_radian3rd->expand();
}


/* FUNCTION: An empty function "to be determined" by whatever algorithm is being implemented.
 * ARGUMENTS: Dependent on usage.
 * RETURN: Returns no values. 
 */
void center::expand()
{
	right->expand();
	up->expand();
	left->expand();
	down->expand();
}




/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
bool gridgraph::invalid_coordinate(unsigned int row, unsigned int column) const
{
	return row < 0 || column < 0 || (gridArray + (row * column)) > END;
}


bool gridgraph::get_coordinate_by_position(unsigned int position, unsigned int & row, unsigned int & column) const
{
	vertex ** target = (gridArray + position);
	if(position < 0 || target > END)
		return false;

	row = (*(target))->get_row_pos();
	column = (*(target))->get_column_pos();
	return true;
}



bool gridgraph::get_position_by_coordinate(unsigned int & position, unsigned int row, unsigned int column) const
{
	if(invalid_coordinate(row, column))
		return false;

	position = (*(gridArray + (row * row_size) + column))->get_position();
	return true;
}


/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */

char gridgraph::get_value_at_cord(unsigned int row, unsigned int column) const 
{
	if(invalid_coordinate(row, column))
		return '\0';
	return (*(gridArray + (row * row_size) + column))->get_value();  
}

void gridgraph::set_value_at_cord(char to_set, unsigned int row, unsigned int column)
{
	if(invalid_coordinate(row, column))
		return;
	(*(gridArray + (row * row_size) + column))->set_value(to_set);
	return;
}


void gridgraph::get_all_values(char * to_get) const
{
	char * temp = to_get;
	vertex ** current = gridArray;
	while(current < END)
	{
		*temp = (*current)->get_value();
		++temp;
		++current;
	}
}
	


void gridgraph::set_all_values(char * to_set)
{
	char * temp = to_set;
	vertex ** current = gridArray;
	while(current < END)
	{
		(*current)->set_value(*temp);
		++temp;
		++current;
	}
}	


