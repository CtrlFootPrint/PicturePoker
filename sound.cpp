#include "sound.h"

namespace Sound
{
    namespace
    {
        sf::Music music;
        sf::SoundBuffer gameover;
        sf::SoundBuffer coin;
        sf::SoundBuffer card;
        sf::SoundBuffer win;
        sf::SoundBuffer lose;
        sf::SoundBuffer draw;
        sf::SoundBuffer box;
        sf::SoundBuffer level_5;
        sf::Sound sound;

    }
    void playMusic()
    {
        music.play();
    }
    void playGameOver()
    {
        sound.setBuffer(gameover);
        sound.play();
    }
    void playCoin()
    {
        sound.setBuffer(coin);
        sound.play();
    }
    void playCard()
    {
        sound.setBuffer(card);
        sound.play();
    }
    void playWin()
    {
        sound.setBuffer(win);
        sound.play();
    }
    void playLose()
    {
        sound.setBuffer(lose);
        sound.play();
    }
    void playDraw()
    {
        sound.setBuffer(draw);
        sound.play();
    }
    void playBox()
    {
        sound.setBuffer(box);
        sound.play();
    }
    void play5level()
    {
        sound.setBuffer(level_5);
        sound.play();
    }
    void initialise()
    {
        music.openFromFile("music.ogg");;
        music.setVolume(50);
        gameover.loadFromFile("gameover.ogg");
        coin.loadFromFile("coin.ogg");
        card.loadFromFile("card.ogg");
        win.loadFromFile("win.ogg");
        lose.loadFromFile("lose.ogg");
        draw.loadFromFile("draw.ogg");
        box.loadFromFile("box.ogg");
        level_5.loadFromFile("5level.ogg");
        music.setLoop(1);
    }
    void quietMusic()
    {
        music.setVolume(25);
    }
    void normalMusic()
    {
        music.setVolume(65);
    }
    void playCondition(int condition)
    {
        if (condition == 0)playLose();
        if (condition == 1)playWin();
        if (condition == 2)playDraw();
    }
}

