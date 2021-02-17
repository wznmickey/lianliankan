#include <bits/stdc++.h>
#include "map.h"
using namespace std;
int main()
{
    Map map = Map(6, 6, 6);
    map.shuffle();
    while (!map.check())
    {
        map.draw();
        map.shuffle();
    }

    map.draw();

    while (true)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (map.connect(Location(x1, y1), Location(x2, y2)))
        {
            map.remove(Location(x1, y1), Location(x2, y2));
        }
        while (!map.check())
            map.shuffle();
        map.draw();
    }
    return 0;
}