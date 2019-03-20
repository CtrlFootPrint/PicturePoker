#include "coin.h"

namespace Coin
{
    namespace
    {
        Numbers coin_counter(23,4);
        Numbers increase_counter(121,88);
        int coin_amount = 10;
         // Amount of coins the player gets
        int coin_bet_total = 1; // Amount of coins betted
        int coin_increase = 0;
        bool drawCoinsBetted = 1;
        bool drawIncreaseCoin = 0;
        Sprite coin_sprite[7]; // 0-4 Betted coins, 5 The coin for the counter, 6 The "Increase" Coin
    }
    void draw()
    {
        for (int i = 0; i<5; i++)
        {
            coin_sprite[i].setTexture(39);
            coin_sprite[i].setLengths(14,16);
            coin_sprite[i].setCoordinates(240-i*18,0);
            if (coin_bet_total>=(i+1) && drawCoinsBetted)coin_sprite[i].draw();
        }
        coin_sprite[5].setTexture(39);
        coin_sprite[5].setCoordinates(6,4);
        coin_sprite[5].draw();
        if (drawIncreaseCoin)
        {
            coin_sprite[6].setTexture(39);
            coin_sprite[6].setCoordinates(104,88);
            coin_sprite[6].draw();
        }

    }
    void increment()
    {
        if (coin_bet_total < 5 && coin_amount > 0)
        {
            coin_bet_total++;
            coin_amount--;
        }
    }
    void reset(int level)
    {
        if (level<5) coin_bet_total = 1;
        else if (level<10) coin_bet_total = 2;
        else if (level<15) coin_bet_total = 3;
        else if (level>=15) coin_bet_total = 4;

        coin_amount-=coin_bet_total;
        coin_increase = 0;
        showBettedCoins();
        hideIncreaseCoin();
    }
    void initialise()
    {
        coin_amount = 10;
         // Amount of coins the player gets
        coin_bet_total = 1;
        coin_amount--;
        coin_increase = 0;
        showBettedCoins();
        hideIncreaseCoin();
    }
    void determineCoinIncrease(int condition, int hand_rank)
    {
        if (condition == 0) // Lose
        {
            coin_increase = -1*coin_bet_total;
        }
        else if (condition == 1) //Win
        {
            int multiplier = 2;

            if (hand_rank == 1) multiplier = 2;
            else if (hand_rank == 2) multiplier = 3;
            else if (hand_rank == 3) multiplier = 4;
            else if (hand_rank == 4) multiplier = 6;
            else if (hand_rank == 5) multiplier = 8;
            else if (hand_rank == 6) multiplier = 16;
            coin_increase = coin_bet_total * multiplier;
            coin_amount+=coin_increase; // Player gets money back betted, and the new difference
            if (coin_amount > 9999) coin_amount = 9999;

        }
        else if (condition == 2) // Draw
        {
            coin_increase = 0;
            coin_amount+=coin_bet_total;
        }

    }
    int getCoinAmount()
    {
        return coin_amount;
    }
    int getCoinBetTotal()
    {
        return coin_bet_total;
    }
    int getCoinIncrease()
    {
        return coin_increase;
    }
    void drawCoinCounter()
    {
        coin_counter.draw(getCoinAmount());
    }
    void hideBettedCoins()
    {
        drawCoinsBetted = 0;
    }
    void showBettedCoins()
    {
        drawCoinsBetted = 1;
    }
    void hideIncreaseCoin()
    {
        drawIncreaseCoin = 0;
    }
    void showIncreaseCoin()
    {
        drawIncreaseCoin = 1;
    }
    void drawCoinIncrease()
    {
        increase_counter.drawSigned(Coin::getCoinIncrease());
    }
    bool checkForGameOver()
    {
        if (coin_amount <= 0) return 1;
        else return 0;
    }
}

namespace Level
{
    namespace
    {
        Numbers level_counter(114,1); // Counter for the level on the top
        Numbers big_star_counter(167,86); // Counter for the extra multiple of 5 level transition
        int level = 0;
        Sprite big_star_sprite;
        Sprite little_star_sprite;
        Sprite x_sprite;
        Sprite level_text_sprite;
    }
    void increment()
    {
        if (level<99)level++;
    }
    void decrement()
    {
        if (level>0) level--;
    }
    int getLevel()
    {
        return level;
    }
    void drawLevel()
    {
        level_text_sprite.setCoordinates(79,87);
        level_text_sprite.setTexture(98);
        level_text_sprite.draw();
        big_star_sprite.setCoordinates(162,82);
        big_star_sprite.setTexture(95);
        big_star_sprite.draw();
        big_star_counter.drawLittleRed(getLevel());
    }
    void drawLevelCounter()
    {
        if (level>0)
        {
            little_star_sprite.setCoordinates(79,0);
            little_star_sprite.setTexture(96);
            little_star_sprite.draw();
            x_sprite.setCoordinates(97,1);
            x_sprite.setTexture(97);
            x_sprite.draw();
            level_counter.draw(getLevel());
        }
    }
    void determineLevelIncrease(int condition)
    {
        if (condition == 0)decrement();
        if (condition == 1)increment();

    }
    void reset()
    {
        level = 0;
    }
    bool isMultipleOfFive()
     {
         if (level%5 == 0 && level!=0) return 1;
         else return 0;
     }
}
