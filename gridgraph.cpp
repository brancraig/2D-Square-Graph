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
corner::corner(const unsigned int & pos, const unsigned int & x, const unsigned int & y) : vertex(pos,x,y)
{}


/* FUNCTION: Constructor for a side vertex.
 * ARGUMENTS: the position of the vertex along the array of vertices, and its position (x, y) in the grid.
 * RETURN: Returns no values.
 */
side::side(const unsigned int & pos, const unsigned int & x, const unsigned int & y) : vertex(pos,x,y)
{}


/* FUNCTION: Constructor for a center vertex.
 * ARGUMENTS: the position of the vertex along the array of vertices, and its position (x, y) in the grid.
 * RETURN: Returns no values.
 */
center::center(const unsigned int & pos, const unsigned int & x, const unsigned int & y) : vertex(pos,x,y)
{}



/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
void gridgraph::graph_init()
{
    array_length = row_size * column_size;
    gridArray = new vertex*[array_length];
    END = (gridArray + array_length);

    vertex ** current = gridArray;
    unsigned int array_position = 0;
    //cout << "row size: " << row_size << " column size: " << column_size << endl;
    for(unsigned int row = 0; row < column_size; ++row)
        for(unsigned int column = 0; column < row_size; ++column, ++array_position, ++current){
	    //cout << '(' << row << ", " << column  << ")\n";
            *current = determine_vertex_type(array_position, row, column);
	}

    current = gridArray;
    while(current < END)
    {
        (**current).init(row_size, column_size, gridArray);
        ++current;
    }
}


/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
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



/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
void corner::init(const unsigned int & x_size, const unsigned int & y_size, vertex ** grid) 
{
	   	
   if(row_pos == 0){ //top
        if(column_pos == 0)         //left
        {
            vertical_adj = *(grid + position + x_size);
            horizontal_adj = *(grid + position + 1);
        } else {               //right
            vertical_adj = *(grid + position + x_size);
            horizontal_adj = *(grid + position - 1);
        }
   }else{       //bottom
       if(column_pos == 0)           //left
       {                   
           vertical_adj = *(grid + position - x_size);
           horizontal_adj = *(grid + position + 1);
       }else{                 //right
           vertical_adj = *(grid + position - x_size);
           horizontal_adj = *(grid + position - 1);
       }
   }
}

/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
void side::init(const unsigned int & x_size, const unsigned int & y_size, vertex ** grid) 
{

    if(row_pos == 0) //top side
    {
        pi_radian1st = *(grid + position + 1); //top next right
        pi_radian2nd = *(grid + position - 1); //top next left
        pi_radian3rd = *(grid + position + x_size); //below this side
    }
    else if(column_pos == 0) //left side
    {
        pi_radian1st = *(grid + position + 1); //side next right
        pi_radian2nd = *(grid + position - x_size); //above this side
        pi_radian3rd = *(grid + position + x_size); //below this side

    }
    else if(row_pos == y_size - 1) // bottom side
    {
        pi_radian1st = *(grid + position + 1); //bottom next right
        pi_radian2nd = *(grid + position - x_size); //above this side
        pi_radian3rd = *(grid + position - 1); //bottom next left
    }
    else if(column_pos == x_size - 1) // right side; 
    {
        pi_radian1st = *(grid + position - x_size); //above this side
        pi_radian2nd = *(grid + position - 1); //left of this side
        pi_radian3rd = *(grid + position + x_size); //below this side
    }
    else{}
}






/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
void center::init(const unsigned int & x_size, const unsigned int & y_size, vertex ** grid) 
{
    right = *(grid + position + 1);
    up = *(grid + position - x_size);
    left = *(grid + position - 1);
    down = *(grid + position + x_size);
}




/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
void vertex::set_value(char value)
{
	character = value;
	return;
}


/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
char vertex::get_value(void)
{
	return character;
}



/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
unsigned int vertex::get_row_pos(void) const
{
    return row_pos;
}





/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
unsigned int vertex::get_column_pos(void) const
{
    return column_pos;
}


/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
unsigned int vertex::get_position(void) const
{
    return position;
}


/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
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

/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
corner::~corner()
{}


/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
side::~side()
{}


/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
center::~center()
{}

/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
vertex::~vertex()
{}





/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
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




/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
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




/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
void corner::display()
{
	cout << position << '\t'
	     << "corner\t" << '(' << row_pos << ", " << column_pos << ')' << " -> " 
	     << "((" << vertical_adj->get_row_pos()   << ", " << vertical_adj->get_column_pos()   << ')'  << ", " 
	     << '('  << horizontal_adj->get_row_pos() << ", " << horizontal_adj->get_column_pos() << "))" << endl;
}





/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
void side::display()
{
	cout << position << '\t'
	     << "side\t" << '(' << row_pos << ", " << column_pos << ')' << " -> " 
	     << "((" << pi_radian1st->get_row_pos() << ", " << pi_radian1st->get_column_pos() << ')'  << ", " 
	     << '('  << pi_radian2nd->get_row_pos() << ", " << pi_radian2nd->get_column_pos() << ')'  << ", " 
	     << '('  << pi_radian3rd->get_row_pos() << ", " << pi_radian3rd->get_column_pos() << "))" << endl;
}

/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
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



/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
void vertex::expand(){}


/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
void corner::expand(){}


/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
void side::expand(){}


/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */
void center::expand(){}




/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */

