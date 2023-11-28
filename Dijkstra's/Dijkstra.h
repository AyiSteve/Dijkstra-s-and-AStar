#pragma once
#include <queue>
#include <SFML/Graphics.hpp>
#include "map.h"
#include "global.h"

////Dijkstra algorithm
//this algorithm expand 360 evenly to find the ending cell then find the shorest path
void Dijkstra(Map& map,sf::RenderWindow& window);