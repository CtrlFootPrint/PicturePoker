#include "window.h"
namespace Window
{
    namespace
    {
        sf::RenderWindow window;
        sf::RenderWindow window2;
        sf::Sprite background;
        sf::Texture b_pic;
        sf::Image icon;
    }
    void initialise()
    {
        icon.loadFromFile("windowicon.png");// Load window icon
        icon.createMaskFromColor(sf::Color(0, 196, 64));
        window.create(sf::VideoMode(256,192), "Picture Poker", sf::Style::Titlebar | sf::Style::Close);
        window.setIcon(16,16,icon.getPixelsPtr());
        //window.setFramerateLimit(60);
    }
    void setBackground()
    {
        b_pic.loadFromFile("background.png");
        background.setTexture(b_pic);
        window.draw(background);
    }
    void drawSprite(const sf::Sprite& sprite)
    {
        window.draw(sprite);
    }
    bool isOpen()
    {
        return window.isOpen();
    }
    void display()
    {
        window.display();
    }
    void clear()
    {
        window.clear();
    }
    void pollEvent()
    {
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
            {
                window.close(); // close window when X is pressed
            }
        }
    }
    sf::RenderWindow& getWindow()
    {
        return window;
    }
    void close()
    {
        window.close();
    }
    bool hasFocus()
    {
        return window.hasFocus();
    }

}


