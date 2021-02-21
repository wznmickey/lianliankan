#ifndef MAP_mickey_H
#define MAP_mickey_H

#include "ctime"
#include "fstream"
#include "iostream"
#include "point.h"
#include "queue"
#include "vector"
/*
enum Direction
{
    no,
    x,
    y,
    both
};
*/

class Map
{
public:
    void shuffle( );
    bool check( );
    bool connect( Location a, Location b );
    bool remove( Location a, Location b );
    int  count( Location A, Location B );
    void cleanVisit( );
    void draw( );
    bool win( );
    Map( int x, int y, int type );

private:
    std::vector< std::vector< Point > > map;
    std::vector< std::vector< int > >   visit;
    int                                 x, y;
    int                                 rest;
};

#endif
