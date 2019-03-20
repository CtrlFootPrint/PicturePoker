#ifndef TEXTURES_H
#define TEXTURES_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "window.h"

namespace Texture
{
    void initialise();
    sf::Texture& getRef(int ID);
}
#endif // TEXTURES_H
