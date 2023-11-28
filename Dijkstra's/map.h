#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>


#include "global.h"

class Map
{
private:
	sf::RectangleShape Block;
	std::vector <std::vector <BlockType>> map;

	//being extra and using this as a temp storage for the new map;
	std::vector <std::vector <BlockType>> mapTemp;
	std::vector<std::vector<BlockType>> Record;
	std::vector<std::vector<BlockType>> CleanMap;

	Position homePosition;
	Position endPosition;

	Position latestInput;

public:
	Map();
	void DrawMap(sf::RenderWindow& Window);
	void updateMapOnClick(sf::Vector2i mousePosition, BlockType type);
	void drawBySlope( sf::Vector2i mousePosition, BlockType type );
	//the two method below help me to have the color show while the user puts it's mouse on top of the block but change back to it's original right after
	void updateMapTemp(sf::Vector2i mousePosition, BlockType type);
	void updateMapDefault();
	//

	//update map from previous upload
	void UpdateMapDefaultFromRecord();
	void ClearMap() { map = CleanMap; Record = CleanMap; mapTemp = CleanMap; homePosition = { 0,0 }; endPosition = { 0,0 }; }
	//save how map looks like before the algorithm starts
	void uploadRecord();

	//checking if home and end had only one input 
	void checkType(BlockType type, bool click);

	//update the block with given point instead of calculation
	void updateOnGiven(Position givenPosition, BlockType type);

	//return map
	std::vector <std::vector <BlockType>> return_map() { return map; };
	//return home and end
	Position return_homePosition() { return homePosition; };
	Position return_endPosition() { return endPosition; };

};