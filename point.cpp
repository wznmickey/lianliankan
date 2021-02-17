#include"point.h"
bool operator==(const Location &a, const Location &b)
{
    return (a.x == b.x && a.y == b.y);
}
bool operator!=(const Location &a, const Location &b)
{
    return (!(a == b));
}
bool operator==(const Point &a, const Point &b)
{
    return (a.location == b.location);
}
bool operator!=(const Point &a, const Point &b)
{
    return (!(a.location == b.location));
}
