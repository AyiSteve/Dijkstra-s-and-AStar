#pragma once
#include <queue>
#include <SFML/Graphics.hpp>
#include "map.h"
#include "global.h"

//A Star algorithm
//this technically guess the expected distances of one node from end and see which will cost the lowest lost to expand
void AStar(Map& map, sf::RenderWindow& window);