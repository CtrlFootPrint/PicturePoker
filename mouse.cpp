#include "mouse.h"
namespace Mouse
{
    bool mouse_pressed = 0; // Bool value representing if the mouse has already been pressed

    bool isPressed()
    {
        return sf::Mouse::isButtonPressed(sf::Mouse::Left);
    }
    int getXPos()
    {
        sf::Vector2i localPosition = sf::Mouse::getPosition(Window::getWindow());
        return localPosition.x;
    }
    int getYPos()
    {
        sf::Vector2i localPosition = sf::Mouse::getPosition(Window::getWindow());
        return localPosition.y;
    }
    bool hasNotBeenPressed()
    {
        return !mouse_pressed;
    }
    void setToHasBeenPressed()
    {
        mouse_pressed = 1;
    }
    void setToHasNotBeenPressed()
    {
        mouse_pressed = 0;
    }
}
namespace Key
{
    namespace
    {
        bool before = 0;
    }
    bool XisPressed()
    {
        if (before == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        {
            before = 1;
            return 1;
        }
        else if (before == 1 && !sf::Keyboard::isKeyPressed(sf::Keyboard::X) )
        {
            before = 0;
            return 0;
        }
        else return 0;

    }
}
