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

template<class T>
class vertex
{
    public:
        vertex(void);
        vertex(const unsigned int & array_position, const unsigned int & row_position, const unsigned int & column_position);
        virtual ~vertex(void);
        virtual void display(void) = 0;
        virtual void create_adjacencies(const unsigned int & row_size, const unsigned int & column_size, vertex<T> ** grid) = 0;
	
	virtual void expand() = 0;
	
	void set_visited(bool);
	bool get_visited(void) const;

        void set_value(T to_set);
        T get_value(void) const;
	
	unsigned int get_position(void) const;
        unsigned int get_row_pos(void) const;
        unsigned int get_column_pos(void) const;


    protected:
	T character;
	bool visited;
	

        unsigned int position;
        unsigned int row_pos;
        unsigned int column_pos;
};

template<class T>
class corner : public vertex<T>
{
    public:
        corner(const unsigned int & array_position, const unsigned int & row_position, const unsigned int & column_position);
        ~corner();
        void display();
        void create_adjacencies(const unsigned int & row_size, const unsigned int & column_size, vertex<T> ** grid);

	void expand();

    private:
        vertex<T> * vertical_adj;
        vertex<T> * horizontal_adj;
};

template<class T>
class side : public vertex<T>
{
    public:
        side(const unsigned int & array_position, const unsigned int & row_position, const unsigned int & column_position);
        ~side();
        void display();
        void create_adjacencies(const unsigned int & row_size, const unsigned int & column_size, vertex<T> ** grid);

	void expand();

    private:
        vertex<T> * pi_radian1st;
        vertex<T> * pi_radian2nd;
        vertex<T> * pi_radian3rd;

};

template<class T>
class center : public vertex<T>
{
    public:
        center(const unsigned int & array_position, const unsigned int & row_position, const unsigned int & column_position);
        ~center();
        void display();
        void create_adjacencies(const unsigned int & row_size, const unsigned int & column_size, vertex<T> ** grid);

	void expand();

    private:
        vertex<T> * right;
        vertex<T> * up;
        vertex<T> * left;
        vertex<T> * down;


};

template<class T>
class gridgraph
{
    public:
	gridgraph(int = NUMBER_OF_ROWS, int = NUMBER_OF_COLUMNS);
        gridgraph(const unsigned int & number_of_rows, const unsigned int & number_of_columns);
;
        ~gridgraph();

        void display_vertices(void) const;
        void display_as_grid(void) const;

	bool invalid_coordinate(unsigned int row, unsigned int column) const;
	bool get_coordinate_by_position(unsigned int position, unsigned int & row, unsigned int & column) const;
	bool get_position_by_coordinate(unsigned int & position, unsigned int row, unsigned int column) const;
	
	T get_value_at_cord(unsigned int row, unsigned int column) const; 
	void set_value_at_cord(T to_set, unsigned int row, unsigned int column);

        void get_all_values(T * to_get) const;
        void set_all_values(T * to_set);

	unsigned int get_size(void) const { return array_length; }
	unsigned int get_row_size(void) const { return row_size; }
	unsigned int get_column_size(void) const { return column_size; }
		



    protected:
        vertex<T> ** gridArray;
        vertex<T> ** END;
        unsigned int row_size;
        unsigned int column_size;
        unsigned int array_length;

    private:
        void graph_init();
        vertex<T> * determine_vertex_type(const unsigned int & position, const unsigned int & row, const unsigned int & column);

};
