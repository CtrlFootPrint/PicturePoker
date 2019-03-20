#ifndef MUSIC_H
#define MUSIC_H
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iomanip>
#include <iostream>

namespace Sound
{
    void playMusic();
    void playGameOver();
    void playCoin();
    void playCard();
    void playWin();
    void playLose();
    void playDraw();
    void playBox();
    void play5level();
    void initialise();
    void quietMusic();
    void normalMusic();
    void playCondition(int condition);
}
#endif // MUSIC_H
