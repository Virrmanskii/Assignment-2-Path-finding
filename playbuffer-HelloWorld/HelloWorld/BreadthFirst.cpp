#include "BreadthFirst.h"

vector<Tile*> BreadthFirst::findPath(Tile* start, Tile* target)
{
    //priority queue where true is sorted first?
    queue<BreadthFirstTile> q;

    q.push(BreadthFirstTile(start));
    q.front().visited = true;







    return vector<Tile*>();
}
