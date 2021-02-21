#include "map.h"
#include <iostream>
using namespace std;
ofstream logfile;
int      main( )
{
    logfile.open( "log.txt", ios::app );
    Map map = Map( 6, 6, 6 );
    map.shuffle( );
    while ( ! map.check( ) )
    {
        map.draw( );
        map.shuffle( );
    }
    map.draw( );
    while ( true )
    {
        Location a, b;
        cin >> a >> b;
        if ( map.remove( a, b ) )
        {
            if ( map.win( ) )
            {
                cout << "You win" << endl;
                return 0;
            }
        }
        else
        {
            cout << "wrong" << endl;
        }
        while ( ! map.check( ) ) map.shuffle( );
        map.draw( );
    }
    return 0;
}
