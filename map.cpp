#include "map.h"
using namespace std;
extern ofstream logfile;
Map::Map( int x, int y, int type )
{
    logfile << "init map with" << x << "*" << y << "with" << type << "type" << endl;
    int n = 0;
    int m = 1;
    {
        vector< Point > VPtemp;
        vector< int >   VItemp;
        for ( int j = 0; j <= y + 1; j++ )
        {
            VPtemp.push_back( Point( 0, j, 0 ) );
            VItemp.push_back( 0 );
        }
        map.push_back( VPtemp );
        visit.push_back( VItemp );
    }
    for ( int i = 1; i <= x; i++ )
    {
        vector< Point > VPtemp;
        vector< int >   VItemp;
        VPtemp.push_back( Point( i, 0, 0 ) );
        VItemp.push_back( 0 );
        for ( int j = 1; j <= y; j++ )
        {
            Point Ptemp = Point( i, j, m );
            VPtemp.push_back( Ptemp );
            VItemp.push_back( 0 );
            n++;
            m = n % type + 1;
        }
        VPtemp.push_back( Point( i, y + 1, 0 ) );
        VItemp.push_back( 0 );
        map.push_back( VPtemp );
        visit.push_back( VItemp );
    }
    {
        vector< Point > VPtemp;
        vector< int >   VItemp;
        for ( int j = 0; j <= y + 1; j++ )
        {
            VPtemp.push_back( Point( x + 1, j, 0 ) );
            VItemp.push_back( 0 );
        }
        map.push_back( VPtemp );
        visit.push_back( VItemp );
    }
    this->x = x;
    this->y = y;
    return;
}
bool Map::check( )
{
    logfile << "goto check" << endl;
    for ( int i = 1; i <= x; i++ )
    {
        for ( int j = 1; j <= y; j++ )
        {
            for ( int ii = 1; ii <= x; ii++ )
            {
                for ( int jj = 1; jj <= y; jj++ )
                {
                    if ( Location( i, j ) != Location( ii, jj ) )
                    {
                        if ( connect( Location( i, j ), Location( ii, jj ) ) == true )
                        {
                            logfile << "check return true" << endl;
                            return true;
                        }
                    }
                }
            }
        }
    }
    logfile << "check return false" << endl;
    return false;
}
bool Map::connect( Location a, Location b )
{
    logfile << "goto connect" << endl;
    Point A = map [ a.x ][ a.y ];
    Point B = map [ b.x ][ b.y ];
    logfile << A << B << endl;
    if ( A.type != B.type )
    {
        logfile << "connect return false" << endl;
        return false;
    }
    Map::cleanVisit( );
    int count = Map::count( a, b );
    logfile << "count:" << count << endl;
    if ( count <= 2 )
    {
        logfile << "connect return true" << endl;
        return true;
    }
    logfile << "connect return false" << endl;
    return false;
}
void Map::cleanVisit( )
{
    logfile << "goto cleanVisit" << endl;
    for ( int i = 0; i <= x + 1; i++ )
    {
        for ( int j = 0; j <= y + 1; j++ ) { visit [ i ][ j ] = 0; }
    }
    logfile << "cleanVisit return" << endl;
    return;
}
int Map::count( Location a, Location b )
{
    logfile << "goto count" << endl;
    logfile << "in data:" << a << b << endl;
    queue< Point > Q;
    Q.push( map [ a.x ][ a.y ] );
    visit [ a.x ][ a.y ] = -1;
    while ( ! Q.empty( ) )
    {
        Point now = Q.front( );
        Q.pop( );
        logfile << "queue data:" << now << endl;
        if ( now == map [ b.x ][ b.y ] )
        {
            logfile << "count find result, return" << visit [ now.location.x ][ now.location.y ] << endl;
            return visit [ now.location.x ][ now.location.y ];
        }
        for ( int i = now.location.x - 1; i >= 0; i-- )
        {
            if ( map [ i ][ now.location.y ].type == 0 || map [ i ][ now.location.y ] == map [ b.x ][ b.y ] )
            {
                if ( visit [ i ][ now.location.y ] == 0 )
                {
                    visit [ i ][ now.location.y ] = visit [ now.location.x ][ now.location.y ] + 1;
                    logfile << i << " " << now.location.y << ":" << visit [ i ][ now.location.y ] << endl;
                    if ( visit [ i ][ now.location.y ] >= 4 ) { return 4; }
                    Q.push( map [ i ][ now.location.y ] );
                }
            }
            else
            {
                break;
            }
        }
        for ( int i = now.location.x + 1; i <= x + 1; i++ )
        {
            if ( map [ i ][ now.location.y ].type == 0 || map [ i ][ now.location.y ] == map [ b.x ][ b.y ] )
            {
                if ( visit [ i ][ now.location.y ] == 0 )
                {
                    visit [ i ][ now.location.y ] = visit [ now.location.x ][ now.location.y ] + 1;
                    logfile << i << " " << now.location.y << ":" << visit [ i ][ now.location.y ] << endl;
                    if ( visit [ i ][ now.location.y ] >= 4 ) { return 4; }
                    Q.push( map [ i ][ now.location.y ] );
                }
            }
            else
            {
                break;
            }
        }
        for ( int i = now.location.y - 1; i >= 0; i-- )
        {
            if ( map [ now.location.x ][ i ].type == 0 || map [ now.location.x ][ i ] == map [ b.x ][ b.y ] )
            {
                if ( visit [ now.location.x ][ i ] == 0 )
                {
                    visit [ now.location.x ][ i ] = visit [ now.location.x ][ now.location.y ] + 1;
                    logfile << now.location.x << " " << i << ":" << visit [ now.location.x ][ i ] << endl;
                    if ( visit [ now.location.x ][ i ] >= 4 ) { return 4; }
                    Q.push( map [ now.location.x ][ i ] );
                }
            }
            else
            {
                break;
            }
        }
        for ( int i = now.location.y + 1; i <= y + 1; i++ )
        {
            if ( map [ now.location.x ][ i ].type == 0 || map [ now.location.x ][ i ] == map [ b.x ][ b.y ] )
            {
                if ( visit [ now.location.x ][ i ] == 0 )
                {
                    visit [ now.location.x ][ i ] = visit [ now.location.x ][ now.location.y ] + 1;
                    logfile << now.location.x << " " << i << ":" << visit [ now.location.x ][ i ] << endl;
                    if ( visit [ now.location.x ][ i ] >= 4 ) { return 4; }
                    Q.push( map [ now.location.x ][ i ] );
                }
            }
            else
            {
                break;
            }
        }
    }
    return 4;
}
void Map::shuffle( )
{
    logfile << "goto shuffle" << endl;
    srand( time( NULL ) );

    for ( int i = 0; i < x * y; i++ )
    {
        int j = rand( ) % ( x * y - i ) + i;
        swap( map [ i % x + 1 ][ i / x + 1 ], map [ j % x + 1 ][ j / x + 1 ] );
        map [ i % x + 1 ][ i / x + 1 ].location.x = i % x + 1;
        map [ i % x + 1 ][ i / x + 1 ].location.y = i / x + 1;
        map [ j % x + 1 ][ j / x + 1 ].location.x = j % x + 1;
        map [ j % x + 1 ][ j / x + 1 ].location.y = j / x + 1;
        swap( visit [ i % x + 1 ][ i / x + 1 ], visit [ j % x + 1 ][ j / x + 1 ] );
    }
    return;
}
void Map::draw( )
{
    logfile << "goto draw" << endl;
    cout << endl;
    cout << "    ";
    for ( int j = 1; j <= y; j++ ) { cout << j << "_ "; }
    cout << endl;
    for ( int i = 1; i <= x; i++ )
    {
        cout << i << "_  ";
        for ( int j = 1; j <= y; j++ )
        {
            if ( map [ i ][ j ].type == 0 ) { cout << "   "; }
            else
            {
                cout << map [ i ][ j ].type << "  ";
            }
            logfile << map [ i ][ j ].type << "  ";
        }
        cout << endl;
        logfile << endl;
    }
    cout << endl;
    logfile << "draw return" << endl;
    return;
}
bool Map::remove( Location a, Location b )
{
    logfile << "goto remove" << endl;
    if ( connect( a, b ) )
    {
        map [ a.x ][ a.y ].type = 0;
        map [ b.x ][ b.y ].type = 0;
        logfile << "remove return true";
        return true;
    }
    logfile << "remove return false";
    return false;
}
