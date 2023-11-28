#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <String>
#include "global.h"
//this is just a simple button creatation with decreated font text with sprite
class Button
{
private:

	sf::RectangleShape button;
	sf::Sprite text;


public:
	Button(int PositionX,int PositionY);
	sf::RectangleShape return_button() { return button; };
	void update_color();
	void default_color();
	void DrawMethod(sf::RenderWindow& window,std::string textLink, float CharacterSize, float Line);
};