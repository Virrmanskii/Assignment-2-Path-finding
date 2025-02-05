#include "AStarCost.h"

int AStarCost::calculateHCost(Tile* start, Tile* target)
{
    int X = abs(start->posX - target->posX);
    int Y = abs(start->posY - target->posY);

    //return 10*(X + Y) + (14-2*10) * min(X,Y);
    return X + Y;
}
