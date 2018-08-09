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

template<class T>
gridgraph<T>::gridgraph(int rows_in_grid, int columns_in_grid) : row_size(columns_in_grid), column_size(rows_in_grid)
{
    graph_init();
}


/* FUNCTION: Constructor for the graph when the size of the grid (rows by columns) is given.
 * ARGUMENTS: the number of rows and the number of columns. 
 * RETURN: Returns no values.
 */
template<class T>
gridgraph<T>::gridgraph(const unsigned int & rows_in_grid, const unsigned int & columns_in_grid) : row_size(columns_in_grid), column_size(rows_in_grid)
{
    graph_init();
}


/* FUNCTION: Copy constructor for the gridgraph class
 * ARGUMENTS: Another gridgraph. 
 * RETURN: Returns no values.
 */
template<class T>
gridgraph<T>::gridgraph(const gridgraph<T> & to_copy) : row_size(to_copy.row_size), column_size(to_copy.column_size)
{
   //initialize the new graph	
   graph_init();

   //copy the values
   vertex<T> * dest = *gridArray;
   vertex<T> * source = *to_copy.gridArray;
   vertex<T> * end = *END;
   while(dest < end)
   {
	   dest->set_value(source->get_value());
	   ++dest;
	   ++source;
   }



}

/* FUNCTION: Constructor for abstract base vertex.
 * ARGUMENTS: the position of the vertex along the array of vertices, and its position (x, y) in the grid.
 * RETURN: Returns no values.
 */
template<class T>
vertex<T>::vertex(const unsigned int & pos, const unsigned int & x, const unsigned int & y) : position(pos), row_pos(x), column_pos(y)
{

   visited = false;
}


/* FUNCTION: Constructor for a corner vertex.
 * ARGUMENTS: the position of the vertex along the array of vertices, and its position (x, y) in the grid.
 * RETURN: Returns no values.
 */

template<class T>
corner<T>::corner(const unsigned int & array_position, const unsigned int & row_position, const unsigned int & column_position) : vertex<T>(array_position, row_position, column_position)
{}


/* FUNCTION: Constructor for a side vertex.
 * ARGUMENTS: the position of the vertex along the array of vertices, and its position (x, y) in the grid.
 * RETURN: Returns no values.
 */
template<class T>
side<T>::side(const unsigned int & array_position, const unsigned int & row_position, const unsigned int & column_position) : vertex<T>(array_position, row_position, column_position)
{}


/* FUNCTION: Constructor for a center vertex.
 * ARGUMENTS: the position of the vertex along the array of vertices, and its position (x, y) in the grid.
 * RETURN: Returns no values.
 */

template<class T>
center<T>::center(const unsigned int & array_position, const unsigned int & row_position, const unsigned int & column_position) : vertex<T>(array_position, row_position, column_position)
{}



/* FUNCTION: Function initializes the graph by iterating through the vertices and deducing each vertex's type.
 * ARGUMENTS: None. Class members that are stored in the constructor act as parameters to this function. 
 * RETURN: Returns no values. 
 */
template<class T>
void gridgraph<T>::graph_init()
{
    array_length = row_size * column_size;
    gridArray = new vertex<T>*[array_length];
    END = (gridArray + array_length);

    vertex<T> ** current = gridArray;
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
template<class T>
vertex<T> * gridgraph<T>::determine_vertex_type(const unsigned int & position, const unsigned int & row_position, const unsigned int & column_position)
{
    unsigned int adjacencies = 4;
    
    //cout << position << " " << row_position << " " << row_size << " " << column_position << " " << column_size << endl;
    
    if(row_position == 0 || row_position == column_size - 1)
        --adjacencies;

    if(column_position == 0 || column_position == row_size - 1)
        --adjacencies;

    if(adjacencies == 3)
        return new side<T>(position, row_position, column_position);

    if(adjacencies == 4)
        return new center<T>(position, row_position, column_position);

    if(adjacencies == 2)
        return new corner<T>(position, row_position, column_position);


    return NULL;
}



/* FUNCTION: Tabulates the adjacencies for the corner vertex type and stores them in that vertex.
 * ARGUMENTS: The size of the rows in the grid and the starting address of the vertex array from the gridgraph.
 * RETURN: Returns no values.
 */
template<class T>
void corner<T>::create_adjacencies(const unsigned int & row_size, const unsigned int & column_size, vertex<T> ** grid) 
{
	   	
   if(vertex<T>::row_pos == 0){ //top
        if(vertex<T>::column_pos == 0)         //left
        {
            vertical_adj = *(grid + vertex<T>::position + row_size);
            horizontal_adj = *(grid + vertex<T>::position + 1);
        } else {               //right
            vertical_adj = *(grid + vertex<T>::position + row_size);
            horizontal_adj = *(grid + vertex<T>::position - 1);
        }
   }else{       //bottom
       if(vertex<T>::column_pos == 0)           //left
       {                   
           vertical_adj = *(grid + vertex<T>::position - row_size);
           horizontal_adj = *(grid + vertex<T>::position + 1);
       }else{                 //right
           vertical_adj = *(grid + vertex<T>::position - row_size);
           horizontal_adj = *(grid + vertex<T>::position - 1);
       }
   }
}

/* FUNCTION: Tabulates the adjacencies for the side vertex type and stores them in that vertex.
 * ARGUMENTS: The size of the rows in the grid and the starting address of the vertex array from the gridgraph.
 * RETURN: Returns no values.
 */

template<class T>
void side<T>::create_adjacencies(const unsigned int & row_size, const unsigned int & column_size, vertex<T> ** grid) 
{

    if(vertex<T>::row_pos == 0) //top side
    {
        pi_radian1st = *(grid + vertex<T>::position + 1); //top next right
        pi_radian2nd = *(grid + vertex<T>::position - 1); //top next left
        pi_radian3rd = *(grid + vertex<T>::position + row_size); //below this side
    }
    else if(vertex<T>::column_pos == 0) //left side
    {
        pi_radian1st = *(grid + vertex<T>::position + 1); //side next right
        pi_radian2nd = *(grid + vertex<T>::position - row_size); //above this side
        pi_radian3rd = *(grid + vertex<T>::position + row_size); //below this side

    }
    else if(vertex<T>::row_pos == column_size - 1) // bottom side
    {
        pi_radian1st = *(grid + vertex<T>::position + 1); //bottom next right
        pi_radian2nd = *(grid + vertex<T>::position - row_size); //above this side
        pi_radian3rd = *(grid + vertex<T>::position - 1); //bottom next left
    }
    else if(vertex<T>::column_pos == row_size - 1) // right side; 
    {
        pi_radian1st = *(grid + vertex<T>::position - row_size); //above this side
        pi_radian2nd = *(grid + vertex<T>::position - 1); //left of this side
        pi_radian3rd = *(grid + vertex<T>::position + row_size); //below this side
    }
    else{}
}



/* FUNCTION: Tabulates the adjacencies for the center vertex type and stores them in that vertex.
 * ARGUMENTS: The size of the rows in the grid and the starting address of the vertex array from the gridgraph.
 * RETURN: Returns no values.
 */
template<class T>
void center<T>::create_adjacencies(const unsigned int & row_size, const unsigned int & column_size, vertex<T> ** grid) 
{
    right = *(grid + vertex<T>::position + 1);
    up = *(grid + vertex<T>::position - row_size);
    left = *(grid + vertex<T>::position - 1);
    down = *(grid + vertex<T>::position + row_size);
}




/* FUNCTION: A setter for the "value" contained within a particular vertex.
 * ARGUMENTS: The value to be set.
 * RETURN: Returns void.
 */
template<class T>
void vertex<T>::set_value(T to_set)
{
	value = to_set;
	return;
}


/* FUNCTION: A getter for whatever "value" is contained within a particular vertex. 
 * ARGUMENTS: No params.
 * RETURN: Returns the value of the thing stored within the vertex. 
 */
template<class T>
T vertex<T>::get_value(void) const
{
	return value;
}



/* FUNCTION: A getter that returns the row position of a given vertex.
 * ARGUMENTS: No params. 
 * RETURN: The row position data member. 
 */
template<class T>
unsigned int vertex<T>::get_row_pos(void) const
{
    return row_pos;
}


/* FUNCTION: A getter that returns the columnal position of a given vertex. 
 * ARGUMENTS: No params. 
 * RETURN: The colomn position data member. 
 */
template<class T>
unsigned int vertex<T>::get_column_pos(void) const
{
    return column_pos;
}


/* FUNCTION: A getter that returns the position of the vertex in the array of vertices. 
 * ARGUMENTS: No params.
 * RETURN: The position data member. 
 */
template<class T>
unsigned int vertex<T>::get_position(void) const
{
    return position;
}


/* FUNCTION: Destructor for the gridgraph class. Deletes all dynamically allocated memory.
 * ARGUMENTS: No params.
 * RETURN: Returns no values. 
 */
template<class T>
gridgraph<T>::~gridgraph()
{
    vertex<T> ** temp = gridArray;
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
template<class T>
corner<T>::~corner()
{}


/* FUNCTION: Destructor for the side class. No dynamic memory.
 * ARGUMENTS: No params.
 * RETURN: Returns no values. 
 */
template<class T>
side<T>::~side()
{}


/* FUNCTION: Destructor for the center class. No dynamic memory.
 * ARGUMENTS: No params.
 * RETURN: Returns no values. 
 */
template<class T>
center<T>::~center()
{}


/* FUNCTION: Destructor for the vertex abstract class. No dynamic memory.
 * ARGUMENTS: No params.
 * RETURN: Returns no values. 
 */
template<class T>
vertex<T>::~vertex()
{}





/* FUNCTION: Function to display the entire graph as a simple grid.
 * ARGUMENTS: No params.
 * RETURN: Returns no values.  
 */
template<class T>
void gridgraph<T>::display_as_grid(void) const
{
    cout << endl;
    vertex<T> ** temp = gridArray;
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
template<class T>
void gridgraph<T>::display_vertices(void) const
{
    vertex<T> ** start = gridArray;
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
template<class T>
void corner<T>::display()
{
	cout << vertex<T>::position << '\t'
	     << "corner\t" << '(' << vertex<T>::row_pos << ", " << vertex<T>::column_pos << ')' << " -> " 
	     << "((" << vertical_adj->get_row_pos()   << ", " << vertical_adj->get_column_pos()   << ')'  << ", " 
	     << '('  << horizontal_adj->get_row_pos() << ", " << horizontal_adj->get_column_pos() << "))" << endl;
}


/* FUNCTION: Displays the array, row, and column position, adjacencies, and type, of a side.
 * ARGUMENTS: No params.
 * RETURN: Returns no values.
 */
template<class T>
void side<T>::display()
{
	cout << vertex<T>::position << '\t'
	     << "side\t" << '(' << vertex<T>::row_pos << ", " << vertex<T>::column_pos << ')' << " -> " 
	     << "((" << pi_radian1st->get_row_pos() << ", " << pi_radian1st->get_column_pos() << ')'  << ", " 
	     << '('  << pi_radian2nd->get_row_pos() << ", " << pi_radian2nd->get_column_pos() << ')'  << ", " 
	     << '('  << pi_radian3rd->get_row_pos() << ", " << pi_radian3rd->get_column_pos() << "))" << endl;
}

/* FUNCTION: Displays the array, row, and column position, adjacencies, and type, of a center.
 * ARGUMENTS: No params.
 * RETURN: Returns no values.
 */
template<class T>
void center<T>::display()
{
    cout << vertex<T>::position << '\t'
	 << "center\t" << '(' << vertex<T>::row_pos << ", " << vertex<T>::column_pos << ')' <<  " -> " 
	 << "((" << right->get_row_pos() << ", " << right->get_column_pos() << ')' << ", " 
	 << '('  << up->get_row_pos()    << ", " << up->get_column_pos()    << ')' << ", "
	 << '('  << left->get_row_pos()  << ", " << left->get_column_pos()  << ')' << ", "
	 << '('  << down->get_row_pos()  << ", " << down->get_column_pos()  << "))" << endl;
}



/* FUNCTION: An empty function "to be determined" by whatever algorithm is being implemented.
 * ARGUMENTS: Dependent on usage.
 * RETURN: Returns no values. 
 */
template<class T>
void vertex<T>::expand(){}


/* FUNCTION: An empty function "to be determined" by whatever algorithm is being implemented.
 * ARGUMENTS: Dependent on usage.
 * RETURN: Returns no values. 
 */
template<class T>
void corner<T>::expand()
{
	horizontal_adj->expand();
	vertical_adj->expand();
}


/* FUNCTION: An empty function "to be determined" by whatever algorithm is being implemented.
 * ARGUMENTS: Dependent on usage.
 * RETURN: Returns no values. 
 */
template<class T>
void side<T>::expand(){
	pi_radian1st->expand();
	pi_radian2nd->expand();
	pi_radian3rd->expand();
}


/* FUNCTION: An empty function "to be determined" by whatever algorithm is being implemented.
 * ARGUMENTS: Dependent on usage.
 * RETURN: Returns no values. 
 */
template<class T>
void center<T>::expand()
{
	right->expand();
	up->expand();
	left->expand();
	down->expand();
}




/* FUNCTION: Tests whether or not a pair of coordinates are invalid before dereferecing a pointer on the array.
 * ARGUMENTS: The row and column coordinates.
 * RETURN: True if the values are good. 
 */
template<class T>
bool gridgraph<T>::valid_coordinate(unsigned int row, unsigned int column) const
{
	return !(row < 0 || column < 0 || row > row_size || column > column_size);
}



/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
template<class T>
bool gridgraph<T>::get_coordinate_by_position(unsigned int position, unsigned int & row, unsigned int & column) const
{
	vertex<T> ** target = (gridArray + position);
	if(position < 0 || target > END)
		return false;

	row = (*(target))->get_row_pos();
	column = (*(target))->get_column_pos();
	return true;
}


/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
template<class T>
bool gridgraph<T>::get_position_by_coordinate(unsigned int & position, unsigned int row, unsigned int column) const
{
	if(!valid_coordinate(row, column))
		return false;

	position = (*(gridArray + (row * row_size) + column))->get_position();
	return true;
}


/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
template<class T>
T gridgraph<T>::get_value_at_cord(unsigned int row, unsigned int column) const 
{
	if(!valid_coordinate(row, column))
		return (T) NULL;
	return (*(gridArray + (row * row_size) + column))->get_value();  
}


/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */

template<class T>
void gridgraph<T>::set_value_at_cord(T to_set, unsigned int row, unsigned int column)
{
	if(!valid_coordinate(row, column))
		return;
	(*(gridArray + (row * row_size) + column))->set_value(to_set);
	return;
}


/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */

template<class T>
void gridgraph<T>::get_all_values(T * to_get) const
{
	T * temp = to_get;
	vertex<T> ** current = gridArray;
	while(current < END)
	{
		*temp = (*current)->get_value();
		++temp;
		++current;
	}
}
	

/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */

template<class T>
void gridgraph<T>::set_all_values(T * to_set)
{
	T * temp = to_set;
	vertex<T> ** current = gridArray;
	while(current < END)
	{
		(*current)->set_value(*temp);
		++temp;
		++current;
	}
}	



template class gridgraph<char>;
template class vertex<char>;
template class side<char>;
template class corner<char>;
template class center<char>;
