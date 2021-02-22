#ifndef TIME_mickey_H
#define TIME_mickey_H

#include <ctime>
#include <utility>
class Time
{
public:
    Time( );
    void             time_add( time_t x );
    std::pair< int, int > getTime( );

private:
    time_t time_begin, time_allowed;
}

#endif