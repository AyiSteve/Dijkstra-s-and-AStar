#include "map.h"

Map::Map(): Block (sf::Vector2f(BlockSize,BlockSize )), latestInput (0,0), homePosition (0,0), endPosition(0,0)
{
	std::vector<BlockType> row(NumBlock, empty);

	for (int y = 0; y< NumBlock; y++ )
	{

		map.push_back(row);

	}

	mapTemp = map;
	Record = map;
	CleanMap = map;
}

void Map::updateOnGiven(Position givenPosition, BlockType type)
{

	map[givenPosition.y][givenPosition.x] = type;
	mapTemp = map;

}

void Map::DrawMap(sf::RenderWindow& Window)
{
	for (int y = 0; y < NumBlock; y++)
	{
		for (int x = 0; x < NumBlock; x++)
		{
			Block.setPosition(x * BlockSize + BlockSpace*x, y * BlockSize + BlockSpace*y);

			switch (map[y][x])
			{
			case empty:
				Block.setFillColor(sf::Color(0, 19, 163));
				break;
			case wall:
				Block.setFillColor(sf::Color::White);
				break;
			case end:
				Block.setFillColor(sf::Color::Red);
				break;
			case home:
				Block.setFillColor(sf::Color::Cyan);
				break;
			case searched:
				Block.setFillColor(sf::Color::Magenta);
				break;
			case path:
				Block.setFillColor(sf::Color::Yellow);
				break;
			}

			Window.draw(Block);
		}

	}
}

//update with click
void Map::updateMapOnClick(sf::Vector2i mousePosition, BlockType type)
{
	latestInput = { (mousePosition.x / (int)Resize) / ((int)BlockSize + (int)BlockSpace),(mousePosition.y / (int)Resize) / ((int)BlockSize + (int)BlockSpace) };
	checkType(type,true);
	map[latestInput.y][latestInput.x] = type;
	mapTemp = map;
}

//update with line
void Map::drawBySlope(sf::Vector2i mousePosition, BlockType type)
{

	Position mouseVector{ (mousePosition.x / (int)Resize) / ((int)BlockSize + (int)BlockSpace),(mousePosition.y / (int)Resize) / ((int)BlockSize + (int)BlockSpace)};
	Position Slope{ mouseVector.x - latestInput.x, mouseVector.y - latestInput.y };

	int x{ (int)latestInput.x };
	int y{ (int)latestInput.y };
	while (x != mouseVector.x || y != mouseVector.y)
	{
		if (x > mouseVector.x)
		{
			x--;
		}     

		else if (x < mouseVector.x)
		{
			x++;
		}

		if (y > mouseVector.y)
		{
			y--;
		}

		else if (y < mouseVector.y)
		{
			y++;
		}

		map[y][x] = type;

	}

	latestInput = mouseVector;
	checkType(type,true);

	mapTemp = map;

}

//show the color while mouse is on map
void Map::updateMapTemp(sf::Vector2i mousePosition, BlockType type)
{
	checkType(type,false);
	map[(mousePosition.y/Resize) / (BlockSize + BlockSpace)][(mousePosition.x/Resize) / (BlockSize + BlockSpace)] = type;
}

//default everytime mouse pop out the map
void Map::updateMapDefault()
{
	map = mapTemp;
}
void Map::UpdateMapDefaultFromRecord()
{
	map = Record;
	mapTemp = Record;
}

void Map::uploadRecord()
{
	Record = map;
}

//make sure there is only one home or end on map
void Map::checkType(BlockType type, bool click)
{
	
	if (type == home)
	{
		if (map[homePosition.y][homePosition.x] == home)
		{
			map[homePosition.y][homePosition.x] = empty;
		}

		if (click == true)
		{
			homePosition.x = latestInput.x;
			homePosition.y = latestInput.y;
		}
	}

	else if (type == end)
	{
		if (map[endPosition.y][endPosition.x] == end)
		{
			map[endPosition.y][endPosition.x] = empty;
		}

		if (click == true)
		{
			endPosition.x = latestInput.x;
			endPosition.y = latestInput.y;
		}
	}
}
