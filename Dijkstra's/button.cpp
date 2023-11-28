#include "button.h"

Button::Button(int PositionX, int PositionY):button(sf::Vector2f (ButtonSizeX,ButtonSizeY))
{

    button.setOrigin(ButtonSizeX / 2, ButtonSizeY / 2);
    button.setPosition(PositionX, PositionY);

    text.setPosition(PositionX, PositionY);

}

void Button::DrawMethod(sf::RenderWindow& window,std::string textLink, float CharacterSize, float Line)
{
    window.draw(button);

    sf::Texture texture;
    sf::IntRect textureRect;
    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
    texture.loadFromFile(textLink);

    text.setTexture(texture);

    textureRect.left = 0;
    textureRect.top = 6 * ratio_text * Line;
    textureRect.width = CharacterSize * ratio_text;
    textureRect.height = 6 * ratio_text;

    text.setTextureRect(textureRect);

    window.draw(text);
}

void Button::update_color()
{
    button.setFillColor(sf::Color::Blue);
}
void Button::default_color()
{
    button.setFillColor(sf::Color::White);

}