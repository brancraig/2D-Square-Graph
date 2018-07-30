//gridgraph.h

/* Brandon Craig | brandonjcraig00 "at" gmail "dot" com */

/* This is a graph for any N by M (N, M > 1) 2-dimensional square grid. In a square grid there
 * are corner, side, and center vertices. Here each one is treated as its own type derived from
 * an abstract base vertex class. This allows for easy tabulation of adjacency pointers across
 * the grid. In this version, diagonally-adjacent squares are NOT tabulated; only those directly
 * adjacent are kept. For example: corners have 2 adjacent vertices; sides have 3; centers have 4.*/

#include <cstddef>
#include <iostream>


using namespace std;


const int NUMBER_OF_ROWS = 3;
const int NUMBER_OF_COLUMNS = 3;


class vertex
{
    public:
        vertex(void);
        vertex(const unsigned int & position, const unsigned int & row_position, const unsigned int & column_position);
        virtual ~vertex(void);
        virtual void display(void) = 0;
        virtual void init(const unsigned int & row_size, const unsigned int & column_size, vertex ** grid) = 0;
	
	virtual void expand() = 0;
	//void set_visited(bool);

        void set_value(char value);
        char get_value(void);

        unsigned int get_position(void) const;
        unsigned int get_row_pos(void) const;
        unsigned int get_column_pos(void) const;


    protected:
	char character;
	bool visited;
	

        unsigned int position;
        unsigned int row_pos;
        unsigned int column_pos;
};


class corner : public vertex
{
    public:
        corner(const unsigned int & position, const unsigned int & row_pos, const unsigned int & column_pos);
        ~corner();
        void display();
        void init(const unsigned int & x_size, const unsigned int & y_size, vertex ** grid);

	void expand();

    private:
        vertex * vertical_adj;
        vertex * horizontal_adj;
};

class side : public vertex
{
    public:
        side(const unsigned int & position, const unsigned int & x, const unsigned int & y);
        ~side();
        void display();
        void init(const unsigned int & x_size, const unsigned int & y_size, vertex ** grid);

	void expand();

    private:
        vertex * pi_radian1st;
        vertex * pi_radian2nd;
        vertex * pi_radian3rd;

};

class center : public vertex
{
    public:
        center(const unsigned int & position, const unsigned int & x, const unsigned int & y);
        ~center();
        void display();
        void init(const unsigned int & x_size, const unsigned int & y_size, vertex ** grid);

	void expand();

    private:
        vertex * right;
        vertex * up;
        vertex * left;
        vertex * down;


};


class gridgraph
{
    public:
        gridgraph(int = NUMBER_OF_ROWS, int = NUMBER_OF_COLUMNS);
        gridgraph(const unsigned int & number_of_rows, const unsigned int & number_of_columns);
        ~gridgraph();

        void display_vertices(void) const;
        void display_as_grid(void) const;
       


    protected:
        vertex ** gridArray;
        vertex ** END;
        unsigned int row_size;
        unsigned int column_size;
        unsigned int array_length;

    private:
        void graph_init();
        vertex * determine_vertex_type(const unsigned int & position, const unsigned int & row, const unsigned int & column);

};
