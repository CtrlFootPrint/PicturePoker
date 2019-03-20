#include "textures.h"
namespace Texture
{
    namespace
    {
        sf::Texture textures[99];
        sf::Image spritesheet;
    }
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
        textures[39].loadFromImage(spritesheet,sf::IntRect(344,72,14,16)); // Coin
        for (int i = 0; i<10; i++)
        {
            textures[40+i].loadFromImage(spritesheet,sf::IntRect(i*17,184,15,15)); // 0 - 9 yellow numbers
        }
        for (int i = 0; i<11; i++)
        {
            textures[50+i].loadFromImage(spritesheet,sf::IntRect(i*17,202,15,15)); // 0 - 9, + blue numbers + and sign
        }
        for (int i = 0; i<11; i++)
        {
            textures[61+i].loadFromImage(spritesheet,sf::IntRect(i*17,220,15,15)); // 0 - 9, + red numbers + and sign
        }
        for (int i = 0; i<10; i++)
        {
            textures[72+i].loadFromImage(spritesheet,sf::IntRect(74+i*10,148,8,15)); // 0 - 9 yellow smaller numbers
        }
        for (int i = 0; i<10; i++)
        {
            textures[82+i].loadFromImage(spritesheet,sf::IntRect(74+i*10,166,8,15)); // 0 - 9 red smaller numbers
        }
        textures[92].loadFromImage(spritesheet,sf::IntRect(2,242,218,29)); // Game Over
        textures[93].loadFromImage(spritesheet,sf::IntRect(230,190,147,35)); // Play Again
        textures[94].loadFromImage(spritesheet,sf::IntRect(230,228,147,35)); // Quit
        textures[95].loadFromImage(spritesheet,sf::IntRect(286,134,27,26)); // Big Star
        textures[96].loadFromImage(spritesheet,sf::IntRect(360,72,16,16)); // Little Star
        textures[97].loadFromImage(spritesheet,sf::IntRect(170,184,15,15)); // x
        textures[98].loadFromImage(spritesheet,sf::IntRect(104,121,82,15)); // Level
    }
    sf::Texture& getRef(int ID)
    {
        return textures[ID];
    }
}
