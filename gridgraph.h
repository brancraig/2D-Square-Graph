/* Brandon Craig | bracraig "at" pdx "dot" edu 
 * Words Buster */
#include <cstddef>
#include <iostream>

using namespace std;


const int NUMBER_OF_ROWS = 3;
const int NUMBER_OF_COLUMNS = 3;


class vertex
{
    public:
        vertex(void);
        vertex(const unsigned short & position, const unsigned short & x_pos, const unsigned short & y_pos);
        virtual ~vertex(void);
        virtual void display(void) = 0;
        virtual void init(const unsigned short & x_size, const unsigned short & y_size, vertex ** grid) = 0;
        virtual unsigned short expand(unsigned short * original, unsigned short ** to_fill, const unsigned short & size) = 0;

       
        void set_tile_number(const unsigned short & to_set);
        unsigned short get_tile_number(void) const;
        unsigned short get_position(void) const;
        unsigned short get_distance(const unsigned short & x, const unsigned short & y) const;
        unsigned short get_x_pos(void) const;
        unsigned short get_y_pos(void) const;

    protected:
        vertex ** gridArray;
        vertex ** END;
        unsigned short tile_number;
        unsigned short position;
        unsigned short x_pos;
        unsigned short y_pos;

        int map_to_array(const unsigned short &, const unsigned short &, const unsigned short &);
};


class corner : public vertex
{
    public:
        corner(const unsigned short & position, const unsigned short & x_pos, const unsigned short & y_pos);
        ~corner();
        void display();
        void init(const unsigned short & x_size, const unsigned short & y_size, vertex ** grid);
        unsigned short expand(unsigned short * original, unsigned short ** to_fill, const unsigned short & size);

    private:
        vertex * vertical_adj;
        vertex * horizontal_adj;
};

class side : public vertex
{
    public:
        side(const unsigned short & position, const unsigned short & x, const unsigned short & y);
        ~side();
        void display();
        void init(const unsigned short & x_size, const unsigned short & y_size, vertex ** grid);
        unsigned short expand(unsigned short * original, unsigned short ** to_fill, const unsigned short & size);
    private:
        vertex * pi_radian1st;
        vertex * pi_radian2nd;
        vertex * pi_radian3rd;

};

class center : public vertex
{
    public:
        center(const unsigned short & position, const unsigned short & x, const unsigned short & y);
        ~center();
        void display();
        void init(const unsigned short & x_size, const unsigned short & y_size, vertex ** grid);
        unsigned short expand(unsigned short * original, unsigned short ** to_fill, const unsigned short & size); 
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
        gridgraph(const unsigned short & number_of_rows, const unsigned short & number_of_columns);
        ~gridgraph();

        void display_vertices(void) const;
        void display_as_grid(void) const;
       


    protected:
        vertex ** gridArray;
        vertex ** END;
        unsigned short row_size;
        unsigned short column_size;
        unsigned short array_length;

    private:
        void init();
        vertex * map_to_grid(const int & position, const int & row, const int & column);

};
