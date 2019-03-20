#include "window.h"
#include "graphics.h"
#include "loops.h"
int main()
{
    Window::initialise();
    Texture::initialise();
    mainloop::initialise();
    while (Window::isOpen()) // Start game loop
    {
        Window::pollEvent();
        Window::clear();
        Window::setBackground();
        mainloop::run();
        Window::display();
    }
    return 0;
}
