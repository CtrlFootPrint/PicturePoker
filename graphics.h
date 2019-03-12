#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
sf::Sprite bb;
sf::Texture backpic;
sf::Image spritesheet;
sf::Texture textures[39]; // 0 = Hold, 1 = Draw, 2 - 7 Cloud to Star, 8 = Back of Card
// 9 - 15 = Five of a Kind - Junk sprites, 16-18 Too bad, You win, draw
// 19-36 Cloud - Star diagram on left, with green and red highlight too
//37-38 Bet sign
bool boxs = 0;

class Sprite
{
    public:
    sf::Sprite sprite_;
    int x_, y_, ID_;
    int lengthx_, lengthy_;
    void draw(sf::RenderWindow &window)
    {
        sprite_.setTexture(textures[ID_]);
        sprite_.setPosition(x_,y_);
        window.draw(sprite_);
    }
    void setCoordinates (int x, int y)
    {
        x_ = x;
        y_ = y;
    }
    void setLengths (int x, int y)
    {
        lengthx_ = x;
        lengthy_ = y;
    }
    void setTexture (int ID)
    {
        ID_ = ID;
    }
    bool isPressed (sf::Vector2i localPosition)
    {
        if ( (localPosition.x >=x_ && localPosition.x <= (x_+lengthx_-1)) && (localPosition.y >=y_ && localPosition.y <= (y_+lengthy_-1)) )
        {
            return 1;
        }
        else return 0;
    }
};
Sprite box;
Sprite bet;
//void s

void initialise()
{
    spritesheet.loadFromFile("spritesheet.png");
    spritesheet.createMaskFromColor(sf::Color(0, 196, 64));
    textures[0].loadFromImage(spritesheet,sf::IntRect(232,0,144,32)); // hold
    textures[1].loadFromImage(spritesheet,sf::IntRect(232,33,144,32)); // draw
    for (int i = 0; i<7; i++)
    {
        textures[2+i].loadFromImage(spritesheet,sf::IntRect(33*i,0,32,48)); // Load textures of cards
    }
    textures[9].loadFromImage(spritesheet,sf::IntRect(200,164,46,15)); // Junk
    textures[10].loadFromImage(spritesheet,sf::IntRect(200,148,55,15)); // 1 Pair
    textures[11].loadFromImage(spritesheet,sf::IntRect(200,132,70,15)); // 2 Pairs
    textures[12].loadFromImage(spritesheet,sf::IntRect(200,116,107,15)); // 3 of a Kind
    textures[13].loadFromImage(spritesheet,sf::IntRect(200,100,103,15)); // Full House
    textures[14].loadFromImage(spritesheet,sf::IntRect(200,84,110,15)); // 4 of a Kind
    textures[15].loadFromImage(spritesheet,sf::IntRect(200,68,108,15)); // 5 of a Kind
    textures[16].loadFromImage(spritesheet,sf::IntRect(0,49,175,30)); // Too Bad
    textures[17].loadFromImage(spritesheet,sf::IntRect(0,80,177,32)); // You Win!
    textures[18].loadFromImage(spritesheet,sf::IntRect(0,114,99,30)); // Draw
    for (int i = 0; i<3; i++) // i = 0 white, = 1 green, = 2 red
    {
        textures[19+6*i].loadFromImage(spritesheet,sf::IntRect(315+21*i,172,20,17)); // Cloud
        for (int j = 0; j<5; j++)
        {
            textures[20+6*i+j].loadFromImage(spritesheet,sf::IntRect(315+21*i,156-j*16,20,16)); // Mushroom - Star
        }
    }
    textures[37].loadFromImage(spritesheet,sf::IntRect(0,147,35,35)); // Bet Orange
    textures[38].loadFromImage(spritesheet,sf::IntRect(37,147,35,35)); // Bet Yellow
    backpic.loadFromFile("background.png");
    bb.setTexture(backpic);
    box.setCoordinates(56,72);
    box.setLengths(144,32); // between 56 and 56+144-1, 72 and 72+32-1
    bet.setCoordinates(3,31);
    bet.setLengths(35,35);
}
#endif GRAPHICS_H
