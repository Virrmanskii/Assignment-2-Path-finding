#include "BreadthFirst.h"

vector<Tile*> BreadthFirst::findPath(Tile* start, Tile* target)
{
    //priority queue where true is sorted first?
    queue<BreadthFirstTile> q;
    //set<BreadthFirstTile, BreadthFirstTileCondition> visited;
    map<Tile*, bool> visited;

    q.push(BreadthFirstTile(start));
    q.front().visited = true;

    while (!q.empty())
    {
        BreadthFirstTile current = q.front();
        q.pop();

        for (auto neighbor : current.tile->neighbor)
        {
            if (!visited.contains(neighbor))
            {
                neighbor->parent = current.tile;

                if (neighbor == target)
                {
                    return reconstructPath(start, target);
                }

                visited[neighbor] = true;
                neighbor->color = Play::cCyan;
                q.push(BreadthFirstTile(neighbor));
                
            }
        }
         
        
        //for (int i = 0; i < current.neighbors.size(); i++)
        //{
        //    if (current.neighbors[i].visited == false)
        //    {
        //        current.neighbors[i].tile->parent = current.tile;

        //        if (current.neighbors[i].tile == target)
        //        {
        //            return reconstructPath(target);
        //        }

        //        current.visited = true;
        //        visited.insert(current.neighbors[i]);
        //        q.push(current.neighbors[i]);
        //    }
        //}
    }

    return {};
}

vector<Tile*> BreadthFirst::reconstructPath(Tile* start, Tile* target)
{
    vector<Tile*> newPath;

    while (target != start)
    {
        newPath.push_back(target);
        target = target->parent;
    }
    newPath.push_back(start);

    reverse(newPath.begin(), newPath.end());
    return newPath;

    //return vector<Tile*>();
}

void BreadthFirst::drawPath(vector<Tile*> path)
{
    for (auto tile : path)
    {
        if (tile == path[0] || tile == path[path.size() - 1])
        {
            continue;
        }
        tile->color = Play::cBlue;
    }
}
