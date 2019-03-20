#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "textures.h"

namespace Window
{
    void initialise();
    void setBackground();
    bool isOpen();
    void display();
    void clear();
    void pollEvent();
    void drawSprite(const sf::Sprite& sprite);
    sf::RenderWindow& getWindow();
    void close();
    bool hasFocus();
}
#endif // WINDOW_H
