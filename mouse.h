#ifndef MOUSE_H
#define MOUSE_H
#include "window.h"
#include <SFML/Window.hpp>
#include <iostream>
namespace Mouse
{

    bool isPressed();
    bool hasNotBeenPressed(); // Has not been pressed in a previous cycle
    int getXPos();
    int getYPos();
    void setToHasBeenPressed();
    void setToHasNotBeenPressed();
}
namespace Key
{
    bool XisPressed();
}

#endif //   MOUSE_H
