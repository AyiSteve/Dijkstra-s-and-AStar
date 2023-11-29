#include <SFML/Graphics.hpp>

#include "global.h"
#include "map.h"
#include "button.h"
#include "Dijkstra.h"
#include "AStar.h"

//type git push origin master to update
//update button
void update_button(Button& buttonD, Button& buttonA, Button& Clear ,sf::RenderWindow& window, bool& AisStarted, bool& DisStarted, int& ButtonHold, ButtonType& Btype, Map& map)
{

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);


    if ((mousePosition.x/Resize < buttonD.return_button().getPosition().x + (ButtonSizeX/2) && mousePosition.x/Resize > buttonD.return_button().getPosition().x - (ButtonSizeX/2)) && (mousePosition.y/Resize < buttonD.return_button().getPosition().y + (ButtonSizeY/2) && mousePosition.y/Resize > buttonD.return_button().getPosition().y - (ButtonSizeY/2)))
    {
        buttonD.update_color();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            ButtonHold = 0;
            Btype = BDijkstra;

            DisStarted = !DisStarted;
        }

    }

    else
    {
        buttonD.default_color();
    }

    if ((mousePosition.x / Resize < buttonA.return_button().getPosition().x + (ButtonSizeX / 2) && mousePosition.x / Resize > buttonA.return_button().getPosition().x - (ButtonSizeX / 2)) && (mousePosition.y / Resize < buttonA.return_button().getPosition().y + (ButtonSizeY / 2) && mousePosition.y / Resize > buttonA.return_button().getPosition().y - (ButtonSizeY / 2)))
    {
        buttonA.update_color();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            ButtonHold = 0;
            Btype = BAStar;
            AisStarted = !AisStarted;
        }

    }

    else
    {
        buttonA.default_color();
    }

    if ((mousePosition.x / Resize < Clear.return_button().getPosition().x + (ButtonSizeX / 2) && mousePosition.x / Resize > Clear.return_button().getPosition().x - (ButtonSizeX / 2)) && (mousePosition.y / Resize < Clear.return_button().getPosition().y + (ButtonSizeY / 2) && mousePosition.y / Resize > Clear.return_button().getPosition().y - (ButtonSizeY / 2)))
    {
        Clear.update_color();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            map.ClearMap();
            AisStarted = false;
            DisStarted = false;

        }

    }

    else
    {
        Clear.default_color();
    }


}

//update map
void update_map(Map& map, sf::RenderWindow& window, int& KeyHold)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    map.updateMapDefault();
    BlockType type{ wall};


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
    {
        type = home;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        type = end;
    }

    if ((mousePosition.x / Resize > 0 && mousePosition.x / Resize < (BlockSize + BlockSpace) * NumBlock) && (mousePosition.y / Resize > 0 && mousePosition.y / Resize < (BlockSize + BlockSpace) * NumBlock))
    {
        map.updateMapTemp(mousePosition, type);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) )
        {
            KeyHold++;
            if (KeyHold < 10 || (type == home || type == end))
            {
                map.updateMapOnClick(mousePosition, type);
            }

            else
            {
                map.drawBySlope(mousePosition, type);
            }
        }

        else
        {
            KeyHold = 0;

        }
    }

 

}


int main()
{
    //create window
    sf::RenderWindow window(sf::VideoMode(Resize * Window_Width, Resize * Window_Length), "Pathfinding", sf::Style::Close);
    window.setView(sf::View(sf::FloatRect(0, 0, Window_Width, Window_Length)));    
    window.setFramerateLimit(60);

    //set up
    int keyHold{ 0 };
    int ButtonHold{ 0 };
    int Atimes = 0;
    int Dtimes = 0;

    bool DisStarted = false;
    bool AisStarted = false;

    Map map;
    ButtonType Btype;
    Button buttonD(Window_Width - 100, 300);
    Button buttonA(Window_Width - 100, 250);
    Button Clear(Window_Width - 100, 200);

    std::vector<std::vector<int>> Distancevector;




    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        //making sure system ain't taking single input more then once
        if (ButtonHold > 10)
        {
             update_button(buttonD, buttonA, Clear, window, AisStarted, DisStarted,ButtonHold,Btype,map);
        }
        else
        {
            ButtonHold++;
        }

        if (!AisStarted && !DisStarted)
        //Map Changes
        update_map(map, window,keyHold);

        //making sure the algorithm ain't overlapping each others
        if (AisStarted && Atimes == 0)
        {
            if (DisStarted)
            {
                map.UpdateMapDefaultFromRecord();
            }
            map.uploadRecord();
            AStar(map, window);
             Atimes++;

             DisStarted = false;
             Dtimes = 0;
        }

        else if (!AisStarted && Atimes == 1)
        {
            map.UpdateMapDefaultFromRecord();
            Atimes = 0;
           
        }

        else if (DisStarted && Dtimes == 0)
        {
            if (AisStarted)
            {
                map.UpdateMapDefaultFromRecord();
            }
            map.uploadRecord();
            Dijkstra(map, window);
            Dtimes++;

            AisStarted = false;
            Atimes = 0;

        }

        else if (!DisStarted && Dtimes == 1)
        {
            map.UpdateMapDefaultFromRecord();
            Dtimes = 0;

        }






        //draw method ok 
        window.clear(sf::Color::Black);
        map.DrawMap(window);
        buttonD.DrawMethod(window, "Start.png", DCharacterSize,DLine);
        buttonA.DrawMethod(window, "Start.png", ACharacterSize,ALine);
        Clear.DrawMethod(window, "Start.png", CCharacterSize, CLine);

        window.display();

    }

    
    return 0;
}
