#include "map.h"
using namespace std;
Map::Map(int x, int y, int type)
{
    int n = 0;
    int m = 1;
    {
        vector<Point> VPtemp;
        vector<int> VItemp;
        for (int j = 0; j <= y + 1; j++)
        {
            VPtemp.push_back(Point(0, j, 0));
            VItemp.push_back(0);
        }
        map.push_back(VPtemp);
        visit.push_back(VItemp);
    }
    for (int i = 1; i <= x; i++)
    {
        vector<Point> VPtemp;
        vector<int> VItemp;
        VPtemp.push_back(Point(i, 0, 0));
        VItemp.push_back(0);
        for (int j = 1; j <= y; j++)
        {
            Point Ptemp = Point(i, j, m);
            VPtemp.push_back(Ptemp);
            VItemp.push_back(0);
            n++;
            m = n % type + 1;
        }
        VPtemp.push_back(Point(i, y + 1, 0));
        VItemp.push_back(0);
        map.push_back(VPtemp);
        visit.push_back(VItemp);
    }
    {
        vector<Point> VPtemp;
        vector<int> VItemp;
        for (int j = 0; j <= y + 1; j++)
        {
            VPtemp.push_back(Point(x + 1, j, 0));
            VItemp.push_back(0);
        }
        map.push_back(VPtemp);
        visit.push_back(VItemp);
    }
    this->x = x;
    this->y = y;
    return;
}
bool Map::check()
{
    for (int i = 1; i <= x; i++)
    {
        for (int j = 1; j <= y; j++)
        {
            for (int ii = 1; ii <= x; ii++)
            {
                for (int jj = 1; jj <= y; jj++)
                {
                    if (Location(i, j) != Location(ii, jj))
                    {
                        if (connect(Location(i, j), Location(ii, jj)) == true)
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}
bool Map::connect(Location a, Location b)
{
    Point A = map[a.x][a.y];
    Point B = map[b.x][b.y];
    if (A.type != B.type)
        return false;
    //Map::cleanVisit();
    //cout << Map::count(a, b);
    Map::cleanVisit();
    if (Map::count(a, b) <= 2)
    {
        return true;
    }
    return false;
}
void Map::cleanVisit()
{
    for (int i = 0; i <= x + 1; i++)
    {
        for (int j = 0; j <= y + 1; j++)
        {
            visit[i][j] = 0;
        }
    }
    return;
}
int Map::count(Location a, Location b)
{
    //cout << "firstcheck" << map[a.x][a.y].location.x << map[a.x][a.y].location.y << endl;
    queue<Point> Q;
    Q.push(map[a.x][a.y]);
    while (!Q.empty())
    {
        Point now = Q.front();
        //cout << "check" << now.location.x << now.location.y << endl;
        Q.pop();
        if (now == map[b.x][b.y])
        {
            return visit[now.location.x][now.location.y];
        }
        for (int i = now.location.x - 1; i >= 0; i--)
        {
            if (map[i][now.location.y].type == 0 || map[i][now.location.y] == map[b.x][b.y])
            {
                if (visit[i][now.location.y] == 0)
                {
                    visit[i][now.location.y] = visit[now.location.x][now.location.y] + 1;
                    if (visit[i][now.location.y] >= 3)
                    {
                        //cout << i << now.location.y << endl;
                        return 3;
                    }
                    Q.push(map[i][now.location.y]);
                }
            }
        }
        for (int i = now.location.x + 1; i <= x + 1; i++)
        {
            if (map[i][now.location.y].type == 0 || map[i][now.location.y] == map[b.x][b.y])
            {
                if (visit[i][now.location.y] == 0)
                {
                    visit[i][now.location.y] = visit[now.location.x][now.location.y] + 1;
                    if (visit[i][now.location.y] >= 3)
                    {
                        //cout << i << now.location.y << endl;
                        return 3;
                    }
                    Q.push(map[i][now.location.y]);
                }
            }
        }
        for (int i = now.location.y - 1; i >= 0; i--)
        {
            if (map[now.location.x][i].type == 0 || map[now.location.x][i] == map[b.x][b.y])
            {
                if (visit[now.location.x][i] == 0)
                {
                    visit[now.location.x][i] = visit[now.location.x][now.location.y] + 1;
                    if (visit[now.location.x][i] >= 3)
                    {
                        //cout << now.location.x << i << endl;
                        return 3;
                    }

                    Q.push(map[now.location.x][i]);
                }
            }
        }
        for (int i = now.location.y + 1; i <= y + 1; i++)
        {
            if (map[now.location.x][i].type == 0 || map[now.location.x][i] == map[b.x][b.y])
            {
                if (visit[now.location.x][i] == 0)
                {
                    visit[now.location.x][i] = visit[now.location.x][now.location.y] + 1;
                    if (visit[now.location.x][i] >= 3)
                    {
                        //cout << now.location.x << i << endl;
                        return 3;
                    }
                    Q.push(map[now.location.x][i]);
                }
            }
        }
    }
    return 3;
}
void Map::shuffle()
{
    srand(time(NULL));

    for (int i = 0; i < x * y; i++)
    {
        int j = rand() % (x * y - i) + i;
        swap(map[i % x + 1][i / x + 1], map[j % x + 1][j / x + 1]);
        map[i % x + 1][i / x + 1].location.x = i % x + 1;
        map[i % x + 1][i / x + 1].location.y = i / x + 1;
        map[j % x + 1][j / x + 1].location.x = j % x + 1;
        map[j % x + 1][j / x + 1].location.y = j / x + 1;
        swap(visit[i % x + 1][i / x + 1], visit[j % x + 1][j / x + 1]);
    }
    return;
}
void Map::draw()
{
    cout << endl;
    for (int i = 1; i <= x; i++)
    {
        for (int j = 1; j <= y; j++)
        {
            cout << map[i][j].type;
        }
        cout << endl;
    }
    cout << endl;
    return;
}
bool Map::remove(Location a, Location b)
{
    if (connect(a, b))
    {
        map[a.x][a.y].type = 0;
        map[b.x][b.y].type = 0;
        return true;
    }
    return false;
}