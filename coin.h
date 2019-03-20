#ifndef COIN_H
#define COIN_H
#include "graphics.h"
#include "othergfx.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Coin
{
    void draw();
    void increment();
    void reset(int level);
    void initialise();
    void determineCoinIncrease(int condition, int hand_rank);
    int getCoinAmount();
    int getCoinBetTotal();
    int getCoinIncrease();
    void drawCoinCounter();
    void drawCoinIncrease();
    void hideBettedCoins();
    void showBettedCoins();
    void showIncreaseCoin();
    void hideIncreaseCoin();
    bool checkForGameOver();
}
namespace Level
{
    int getLevel();
    void increment();
    void decrement();
    void drawLevel();
    void drawLevelCounter();
    void determineLevelIncrease(int condition);
    void reset();
    bool isMultipleOfFive();
}
#endif // COIN_H
