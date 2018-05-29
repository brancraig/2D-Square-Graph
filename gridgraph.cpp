/* Brandon Craig | bracraig "at" pdx "dot" edu 
 * CS441 | Fall 2017 | Portland State University */


#include "gridgraph.h"

/* FUNCTION: Default constructor for the graph when no arguments are given.
 * ARGUMENTS: Uses global constants as parameters (Set in 'gridgraph.h') 
 * RETURN: Returns no values.
 */
gridgraph::gridgraph(int rows_in_grid, int columns_in_grid)
{
    row_size = columns_in_grid;
    column_size = rows_in_grid;
    init();
}


/* FUNCTION: Constructor for the graph when the size of the grid (rows by columns) is given.
 * ARGUMENTS: the number of rows and the number of columns. 
 * RETURN: Returns no values.
 */
gridgraph::gridgraph(const unsigned short & rows_in_grid, const unsigned short & columns_in_grid)
{
    row_size = columns_in_grid;
    column_size = rows_in_grid;
    init();
}


/* FUNCTION: Constructor for abstract base vertex.
 * ARGUMENTS: the position of the vertex along the array of vertices, and its position (x, y) in the grid.
 * RETURN: Returns no values.
 */
vertex::vertex(const unsigned short & pos, const unsigned short & x, const unsigned short & y)
{
    tile_number = 0;
    position = pos;
    x_pos = x;
    y_pos = y;
}


/* FUNCTION: Constructor for a corner vertex.
 * ARGUMENTS: the position of the vertex along the array of vertices, and its position (x, y) in the grid.
 * RETURN: Returns no values.
 */
corner::corner(const unsigned short & pos, const unsigned short & x, const unsigned short & y) : vertex(pos,x,y)
{}


/* FUNCTION: Constructor for a side vertex.
 * ARGUMENTS: the position of the vertex along the array of vertices, and its position (x, y) in the grid.
 * RETURN: Returns no values.
 */
side::side(const unsigned short & pos, const unsigned short & x, const unsigned short & y) : vertex(pos,x,y)
{}


/* FUNCTION: Constructor for a center vertex.
 * ARGUMENTS: the position of the vertex along the array of vertices, and its position (x, y) in the grid.
 * RETURN: Returns no values.
 */
center::center(const unsigned short & pos, const unsigned short & x, const unsigned short & y) : vertex(pos,x,y)
{}



void gridgraph::init()
{
    array_length = row_size * column_size;
    gridArray = new vertex*[array_length];
    END = (gridArray + array_length);

    vertex ** current = gridArray;
    int count = 0;
    for(int row_pos = 0; row_pos < row_size; ++row_pos)
        for(int column_pos = 0; column_pos < column_size; ++column_pos, ++count, ++current)
            *current = map_to_grid(count, row_pos, column_pos);

    current = gridArray;
    while(current < END)
    {
        (**current).init(row_size, column_size, gridArray);
        ++current;
    }
}

vertex * gridgraph::map_to_grid(const int & position, const int & row_pos, const int & column_pos)
{
    int adjacencies = 4;
    
    cout << position << " " << row_pos << " " << row_size << " " << column_pos << " " << column_size << endl;
    
    if(row_pos == 0 || row_pos == column_size - 1)
        --adjacencies;

    if(column_pos == 0 || column_pos == row_size - 1)
        --adjacencies;

    if(adjacencies == 3)
        return new side(position, row_pos, column_pos);

    if(adjacencies == 4)
        return new center(position, row_pos, column_pos);

    if(adjacencies == 2)
        return new corner(position, row_pos, column_pos);


    return NULL;
}



int vertex::map_to_array(const unsigned short & x, const unsigned short & y, const unsigned short & row_size)
{
    return y + (row_size * x);
}


void corner::init(const unsigned short & x_size, const unsigned short & y_size, vertex ** grid) 
{
   if(x_pos == 0){ //top
        if(y_pos == 0)         //left
        {
            vertical_adj = *(grid + map_to_array(x_pos + 1, y_pos, y_size));
            horizontal_adj = *(grid + map_to_array(x_pos, y_pos + 1, y_size));
        } else {               //right
            vertical_adj = *(grid + map_to_array(x_pos + 1, y_pos, y_size));
            horizontal_adj = *(grid + map_to_array(x_pos, y_pos - 1, y_size));
        }
   }else{       //bottom
       if(y_pos == 0)           //left
       {                   
           vertical_adj = *(grid + map_to_array(x_pos - 1, y_pos, y_size));
           horizontal_adj = *(grid + map_to_array(x_pos, y_pos + 1, y_size));
       }else{                 //right
           vertical_adj = *(grid + map_to_array(x_pos - 1, y_pos, y_size));
           horizontal_adj = *(grid + map_to_array(x_pos, y_pos - 1, y_size));
       }
   }
   gridArray = grid;
   END = (gridArray + x_size * y_size);

}


void side::init(const unsigned short & x_size, const unsigned short & y_size, vertex ** grid) 
{

    if(x_pos == 0) //top side
    {
        pi_radian1st = *(grid + map_to_array(x_pos, y_pos + 1, y_size)); //top next right
        pi_radian2nd = *(grid + map_to_array(x_pos, y_pos - 1, y_size)); //top next left
        pi_radian3rd = *(grid + map_to_array(x_pos + 1, y_pos, y_size)); //below this side
    }
    else if(y_pos == 0) //left side
    {
        pi_radian1st = *(grid + map_to_array(x_pos, y_pos + 1, y_size)); //side next right
        pi_radian2nd = *(grid + map_to_array(x_pos - 1, y_pos, y_size)); //above this side
        pi_radian3rd = *(grid + map_to_array(x_pos + 1, y_pos, y_size)); //below this side

    }
    else if(x_pos == x_size - 1) // bottom side
    {
        pi_radian1st = *(grid + map_to_array(x_pos, y_pos + 1, y_size)); //bottom next right
        pi_radian2nd = *(grid + map_to_array(x_pos - 1, y_pos, y_size)); //above this side
        pi_radian3rd = *(grid + map_to_array(x_pos, y_pos - 1, y_size)); //bottom next left
    }
    else if(y_pos == y_size - 1) // right side; 
    {
        pi_radian1st = *(grid + map_to_array(x_pos - 1, y_pos, y_size)); //above this side
        pi_radian2nd = *(grid + map_to_array(x_pos, y_pos - 1, y_size)); //left of this side
        pi_radian3rd = *(grid + map_to_array(x_pos + 1, y_pos, y_size)); //below this side
    }
    else{}
    gridArray = grid;
    END = (gridArray + x_size * y_size);
}

void center::init(const unsigned short & x_size, const unsigned short & y_size, vertex ** grid) 
{
    right = *(grid + map_to_array(x_pos, y_pos + 1, y_size));
    up = *(grid + map_to_array(x_pos - 1, y_pos, y_size));
    left = *(grid + map_to_array(x_pos, y_pos - 1, y_size));
    down = *(grid + map_to_array(x_pos + 1, y_pos, y_size));
    gridArray = grid;
    END = (gridArray + x_size * y_size);

}


void vertex::set_tile_number(const unsigned short & to_set)
{
    tile_number = to_set;
    return;
}


unsigned short vertex::get_tile_number(void) const
{
    return tile_number;
}


unsigned short vertex::get_x_pos(void) const
{
    return x_pos;
}
        
unsigned short vertex::get_y_pos(void) const
{
    return y_pos;
}



unsigned short vertex::get_position(void) const
{
    return position;
}



unsigned short vertex::get_distance(const unsigned short & x, const unsigned short & y) const
{
  return abs(x - x_pos) + abs(y - y_pos);
}



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

corner::~corner()
{}

side::~side()
{}

center::~center()
{}

vertex::~vertex()
{}

void gridgraph::display_as_grid(void) const
{
    cout << endl;
    vertex ** temp = gridArray;
    //unsigned short to_display;
    for(int i = 0; i < column_size; ++i)
    {
        for(int j = 0; j < row_size; ++j)
        {
	
	    cout << '(' << (*temp)->get_x_pos() << ", " << (*temp)->get_y_pos()	<< ')' << '\t';
            ++temp;
        }
        cout << endl << endl;
    }
    cout << endl;
    return;
}





void gridgraph::display_vertices(void) const
{
    vertex ** start = gridArray;
    while(start < END)
    {
        for(int i = 0; i < row_size; ++i, ++start){
            (*start)->display();
            cout << endl;
        }
    }
    cout << endl;
}


void corner::display()
{
	cout << position << '\t'
	     << "corner\t" << '(' << x_pos << ", " << y_pos << ')' << " -> " 
	     << "((" << vertical_adj->get_x_pos()   << ", " << vertical_adj->get_y_pos()   << ')'  << ", " 
	     << '('  << horizontal_adj->get_x_pos() << ", " << horizontal_adj->get_y_pos() << "))" << endl;
}

void side::display()
{
	cout << position << '\t'
	     << "side\t" << '(' << x_pos << ", " << y_pos << ')' << " -> " 
	     << "((" << pi_radian1st->get_x_pos() << ", " << pi_radian1st->get_y_pos() << ')'  << ", " 
	     << '('  << pi_radian2nd->get_x_pos() << ", " << pi_radian2nd->get_y_pos() << ')'  << ", " 
	     << '('  << pi_radian3rd->get_x_pos() << ", " << pi_radian3rd->get_y_pos() << "))" << endl;
}

void center::display()
{
    cout << position << '\t'
	 << "center\t" << '(' << x_pos << ", " << y_pos << ')' <<  " -> " 
	 << "((" << right->get_x_pos() << ", " << right->get_y_pos() << ')' << ", " 
	 << '('  << up->get_x_pos()    << ", " << up->get_y_pos()    << ')' << ", "
	 << '('  << left->get_x_pos()  << ", " << left->get_y_pos()  << ')' << ", "
	 << '('  << down->get_x_pos()  << ", " << down->get_y_pos()  << "))" << endl;
}




unsigned short corner::expand(unsigned short * original, unsigned short ** to_fill, const unsigned short & size)
{
    unsigned short * temp1 = *to_fill = new unsigned short[size];
    unsigned short * temp2 = *(to_fill + 1) = new unsigned short[size];
    vertex ** start = gridArray;
    while(start < END)
    {
        *temp1 = *temp2 = (*start)->get_tile_number();
        ++temp1;
        ++temp2;
        ++start;
    }
    unsigned short vert_position = vertical_adj->get_position();
    (*to_fill)[vert_position] = 0;
    (*to_fill)[position] = vertical_adj->get_tile_number();

    unsigned short hori_position = horizontal_adj->get_position();
    (*(to_fill + 1))[hori_position] = 0;
    (*(to_fill + 1))[position] = horizontal_adj->get_tile_number();


    
    return 2;
}


unsigned short side::expand(unsigned short * original, unsigned short ** to_fill, const unsigned short & size)
{
    unsigned short * temp0 = *to_fill = new unsigned short[size];
    unsigned short * temp1 = *(to_fill + 1) = new unsigned short[size];
    unsigned short * temp2 = *(to_fill + 2) = new unsigned short[size];

    vertex ** start = gridArray;
    while(start < END)
    {
        *temp0 = *temp1 = *temp2 = (*start)->get_tile_number();
        ++temp0;
        ++temp1;
        ++temp2;
        ++start;
    }
    unsigned short first_pos = pi_radian1st->get_position();
    (*to_fill)[first_pos] = 0;
    (*to_fill)[position] = pi_radian1st->get_tile_number();

    unsigned short second_pos = pi_radian2nd->get_position();
    (*(to_fill + 1))[second_pos] = 0;
    (*(to_fill + 1))[position] = pi_radian2nd->get_tile_number();

    unsigned short third_pos = pi_radian3rd->get_position();
    (*(to_fill + 2))[third_pos] = 0;
    (*(to_fill + 2))[position] = pi_radian3rd->get_tile_number();

    return 3;
}

unsigned short center::expand(unsigned short * original, unsigned short ** to_fill, const unsigned short & size)
{
    unsigned short * temp0 = *to_fill = new unsigned short[size];
    unsigned short * temp1 = *(to_fill + 1) = new unsigned short[size];
    unsigned short * temp2 = *(to_fill + 2) = new unsigned short[size];
    unsigned short * temp3 = *(to_fill + 3) = new unsigned short[size];

    vertex ** start = gridArray;
    while(start < END)
    {
        *temp0 = *temp1 = *temp2 = *temp3 = (*start)->get_tile_number();
        ++temp0;
        ++temp1;
        ++temp2;
        ++temp3;
        ++start;
    }
    unsigned short first_pos = right->get_position();
    (*to_fill)[first_pos] = 0;
    (*to_fill)[position] = right->get_tile_number();

    unsigned short second_pos = up->get_position();
    (*(to_fill + 1))[second_pos] = 0;
    (*(to_fill + 1))[position] = up->get_tile_number();

    unsigned short third_pos = left->get_position();
    (*(to_fill + 2))[third_pos] = 0;
    (*(to_fill + 2))[position] = left->get_tile_number();

    unsigned short fourth_pos = down->get_position();
    (*(to_fill + 3))[fourth_pos] = 0;
    (*(to_fill + 3))[position] = down->get_tile_number();

    return 4;
}

/* FUNCTION:
 * ARGUMENTS:
 * RETURN:
 */

