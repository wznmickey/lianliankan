#include "point.h"
using namespace std;
bool operator==( const Location &a, const Location &b )
{
    return ( a.x == b.x && a.y == b.y );
}
bool operator!=( const Location &a, const Location &b )
{
    return ( ! ( a == b ) );
}
bool operator==( const Point &a, const Point &b )
{
    return ( a.location == b.location );
}
bool operator!=( const Point &a, const Point &b )
{
    return ( ! ( a.location == b.location ) );
}
ostream &operator<<( ostream &OS, const Location &a )
{
    OS << "x=" << a.x << ",y= " << a.y;
    return OS;
}
istream &operator>>( istream &IS, Location &a )
{
    IS >> a.x >> a.y;
    return IS;
}
ostream &operator<<( ostream &OS, const Point &a )
{
    OS << a.location << ",type= " << a.type;
    return OS;
}
istream &operator>>( istream &IS, Point &a )
{
    IS >> a.location >> a.type;
    return IS;
}