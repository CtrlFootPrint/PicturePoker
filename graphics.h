#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "window.h"
#include "mouse.h"
#include "textures.h"

class Sprite
{
    private:
    int x_, y_, ID_;
    int lengthx_, lengthy_;
    sf::Sprite sprite_;
    public:
    Sprite();
    Sprite (int lengthx, int lengthy, int ID);
    void draw();
    void setCoordinates (int x, int y);
    void setLengths (int x, int y);
    void setTexture (int ID);
    void displaceX (int dis);
    void displaceY (int dis);
    bool isPressed ();
};

#endif // GRAPHICS_H
