#include "DeapthFirst.h"

std::vector<Tile*> DeapthFirst::findPath(Tile* start, Tile* goal)
{
	//stack<DFTile>  stack;
	//map<DFTile, bool> visited;
	stack<Tile*>  stack;
	map<Tile*, bool> visited;

	stack.push(start);

	while (!stack.empty())
	{
		Tile* current = stack.top();
		stack.pop();

		if (current == goal)
		{
			return reconstructPath(start, goal);
		}

		visited[current] = true;

		for (auto neighbor : current->neighbor)
		{
			if (!visited.contains(neighbor))
			{
				neighbor->parent = current;
				stack.push(neighbor);
			}
		}
	}

	return {};
}

vector<Tile*> DeapthFirst::reconstructPath(Tile* start, Tile* target)
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
}
