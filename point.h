#ifndef POINT_mickey_H
#define POINT_mickey_H

#include <bits/stdc++.h>
struct Location
{
    int x, y;
    Location(int x = 0, int y = 0)
    {
        this->x = x;
        this->y = y;
    }
};
class Point
{
public:
    //type==0  => is removed
    int type;
    Location location;
    Point(int x = 0, int y = 0, int type = 0)
    {
        location = Location(x, y);
        this->type = type;
        return;
    }
};
bool operator==(const Location &a, const Location &b);
bool operator!=(const Location &a, const Location &b);
bool operator==(const Point &a, const Point &b);
bool operator!=(const Point &a, const Point &b);
#endif
