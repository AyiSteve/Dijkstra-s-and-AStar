#include "AStar.h"

void AStar(Map& map, sf::RenderWindow& window)
{

	int Distance{};
	//this array put the lowest distance search to the front
	std::priority_queue < Node, std::vector<Node>, std::greater<Node> > myQueue;
	std::vector <Node> storage;

	int y = map.return_homePosition().y;
	int x = map.return_homePosition().x;
	Distance = abs(y - map.return_endPosition().y) + abs(x - map.return_endPosition().x);
	storage.push_back(Node(Position(x, y), Distance, 0, 0, 0));


	myQueue.push(storage[0]);


	bool findEnd{ false };
	while (findEnd == false)
	{

		if (!myQueue.empty())
		{

			Node target = myQueue.top();
			y = target.id.y;
			x = target.id.x;


			int xTemp = { 0 };
			int yTemp = { 0 };
			for (int i = 0; i < 4; i++)
			{

				switch (i)
				{
				case 0:
					xTemp = x - 1;
					yTemp = y;
					break;
				case 1:
					xTemp = x + 1;
					yTemp = y;
					break;

				case 2:
					xTemp = x;
					yTemp = y + 1;
					break;

				case 3:
					xTemp = x;
					yTemp = y - 1;
					break;

				}

				if (xTemp >= 0 && yTemp >= 0 && xTemp < NumBlock && yTemp < NumBlock)
				{
					if (map.return_map()[yTemp][xTemp] == empty)
					{
						Distance = target.distanceReal + 1+ abs( map.return_endPosition().y - yTemp) + abs(  map.return_endPosition().x- xTemp);

						//I saves the expected distances adding up the actual distances
						storage.push_back(Node(Position(xTemp, yTemp), Distance,target.distanceReal+1, target.currentNode, storage.size()));

						myQueue.push(storage[storage.size() - 1]);
						map.updateOnGiven((storage[storage.size() - 1].id), searched);
						window.clear(sf::Color::Black);
						map.DrawMap(window);
						window.display();
					}

					else if (map.return_map()[yTemp][xTemp] == end)
					{

						// child finding mom cell
						Node finalPath = target;

						while (finalPath.currentNode != 0)
						{

							map.updateOnGiven((finalPath.id), path);


							finalPath = storage[finalPath.previousNode];
						}
						findEnd = true;

					}

				}


			}

			myQueue.pop();

		}


	}


}

