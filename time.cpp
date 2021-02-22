#include "time.h"
using namespace std;
Time::Time( )
{
    time_begin = time( NULL );
    return;
}
void Time::time_add( time_t x )
{
    time_allowed += x;
    return;
}
pair< int, int > Time::getTime( )
{
    return make_pair( ( int ) time_begin, ( int ) time_allowed );
}