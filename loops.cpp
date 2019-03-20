#include "loops.h"
// To do list
// Features:
// Incorporate board of hands (1 pair, full house etc...) and winning multipliers
// Improve animations
// Add basic features like a title screen, options
// Code:
// Improve stucture of some class functions, remove redundant ones

namespace mainloop
{
    namespace
    {
        Cardset cpu(16,64,1,1); // Computer's cards
        Cardset hmn(128,112,0,0); // Player's cards
        int mode = 0; // Integer representing the different modes the game will go through
        sf::Clock bet_clock; // Clock reference used for the flashing bet sign
        sf::Clock loop_clock; // Clock reference used to determine how long a mode will be displayed for
    }
    int getMode()
    {
        return mode;
    }
    void run()
    {
        // Determines when each loop will run for
        if (mode == 0)loopOne();
        else if (mode == 1) loopTwo();
        else if (mode == 2) loopThree();
        else if (mode == 3) loopFour();
        else if (mode == 4) loopFive();
        else if (mode == 5) loopSix();
        else if (mode == 6) loopSeven();
        else if (mode == 7) loopEight();
        else if (mode == 8) loopNine();
        else if (mode == 9) loopTen();
        else if (mode == 10) loopEleven();
    }
    void loopOne()
    {
        Level::drawLevelCounter();
        Coin::drawCoinCounter();
        hmn.drawCards();
        cpu.drawCards();
        Diagram::draw(); // Draw diagram that shows ranking of suits
        Box::draw();
        Bet::draw();
        Coin::draw();
        if (oscillate(500) ) Bet::setToFlash0(); else Bet::setToFlash1(); // Flashing bet sign
        if (hmn.NoCardSelected()) Box::setToHold();else Box::setToDraw();
        // Determines what text is written on box. Hold for no cards selected, Draw for at least one
        if (Mouse::isPressed())
        {
            if (Mouse::hasNotBeenPressed()) // Only perform loop if it is first time that mouse has been pressed
            {
                if (Bet::isPressed())
                {
                    if (Coin::getCoinBetTotal() < 5 && Coin::getCoinAmount() > 0) Sound::playCoin();
                    // play coin sound if the coin bet total has been incremented
                    Coin::increment(); // Attempt to increment coin bet total
                }
                Mouse::setToHasBeenPressed(); // Mouse has been pressed to prevent code from running again
                hmn.highlightApplicableCards(Mouse::getXPos(),Mouse::getYPos());// check if cards have been pressed
                if (!hmn.NoCardPressed())Sound::playCard(); // Play card sign if cards have been selected
                if (Box::isPressed())
                {
                    Sound::playBox();
                    hmn.hideApplicableCards(); // Hide the cards have been selected, that will be swapped
                    mode = 1; // Change mode
                    loop_clock.restart(); // Reset timer
                }
            }
        }
        else Mouse::setToHasNotBeenPressed(); // Otherwise wait until mouse has been let go
    }
    void loopTwo()
    {
        Level::drawLevelCounter();
        hmn.drawCards();
        cpu.drawCards();
        Diagram::draw();
        Coin::draw();
        Coin::drawCoinCounter();
        if (hasPassed(500))
        {
            hmn.switchCards(); // switch selected cards with new values
            hmn.uncoverCards(); // Uncover cards that have been swapped
            loop_clock.restart(); // Reset timer
            cpu.AISwitch(); // Make the AI choose their own cards
            mode = 2; // Change mode
        }
    }
    void loopThree()
    {
        Level::drawLevelCounter();
        hmn.drawCards();
        cpu.drawCards();
        Diagram::draw();
        Coin::draw();
        Coin::drawCoinCounter();
        if (hasPassed(750))
        {
            cpu.switchCards(); // switch computer player's cards with new values
            loop_clock.restart(); // reset timer
            mode = 3;
        }
    }
    void loopFour()
    {
        Level::drawLevelCounter();
        hmn.drawCards();
        cpu.drawCards();
        Diagram::draw();
        Coin::draw();
        Coin::drawCoinCounter();
        if (hasPassed(1500))
        {
            hmn.countCards(); // Count the amount of each suit
            hmn.arrangeCards(); //
            hmn.applyArrangement();
            cpu.resetCount();
            cpu.countCards();
            cpu.arrangeCards();
            cpu.applyArrangement();
            cpu.uncoverCards(); // Reveal computer's cards
            mode = 4;
            loop_clock.restart();
        }
    }
    void loopFive()
    {
        Level::drawLevelCounter();
        hmn.drawCards();
        cpu.drawCards();
        Diagram::draw();
        Coin::draw();
        Coin::drawCoinCounter();
        hmn.drawRankGfx();
        cpu.drawRankGfx();
        if (hasPassed(1500))
        {
            if (Diagram::requiresFlash(hmn.getHRank(),cpu.getHRank()))
            { // If diagram needs to flash, determine which diagram blocks will flash
                Diagram::setFlashes(hmn.getHRank(),cpu.getSuit1(),hmn.getSuit1(),cpu.getSuit2(),hmn.getSuit2());
                mode = 5;
            }
            else
            { //Otherwise skip this step and apply condition graphic in the next loop
                mode = 6;
                Condition::whoWins(hmn.getHRank(),cpu.getHRank(),hmn.getSuit1(),cpu.getSuit1(),hmn.getSuit2(),cpu.getSuit2());
                Sound::playCondition(Condition::getCond()); // Play the sound for win, lose or draw
                Level::determineLevelIncrease(Condition::getCond()); // Increase, Decrease or keep level
            }
            loop_clock.restart();
        }
    }
    void loopSix()
    {
        Level::drawLevelCounter();
        hmn.drawCards();
        cpu.drawCards();
        Diagram::draw();
        Coin::draw();
        Coin::drawCoinCounter();
        hmn.drawRankGfx();
        cpu.drawRankGfx();
        if (oscillate(500) && Diagram::requiresFlash(hmn.getHRank(),cpu.getHRank()))
        {
            Diagram::applyFlashOne();
            hmn.determineDisappear(cpu.getSuit1());
            cpu.determineDisappear(hmn.getSuit1());
        }
        else
        {
            hmn.showAll();
            cpu.showAll();
            Diagram::applyFlashTwo();
        } // Apply cards and diagram flash
        if (hasPassed(1750))
        {// Draw win/lose/draw graphic and play respective sound after determining the condition
            mode = 6;
            loop_clock.restart();
            Condition::whoWins(hmn.getHRank(),cpu.getHRank(),hmn.getSuit1(),cpu.getSuit1(),hmn.getSuit2(),cpu.getSuit2());
            Sound::playCondition(Condition::getCond());
            Level::determineLevelIncrease(Condition::getCond());
        }
    }
    void loopSeven()
    {
        Level::drawLevelCounter();
        hmn.drawCards();
        cpu.drawCards();
        Diagram::draw();
        Coin::draw();
        Coin::drawCoinCounter();
        Condition::draw();
        if (oscillate(500) && Diagram::requiresFlash(hmn.getHRank(),cpu.getHRank()))
        {
            Diagram::applyFlashOne();
            hmn.determineDisappear(cpu.getSuit1());
            cpu.determineDisappear(hmn.getSuit1());
        }
        else
        {
            hmn.showAll();
            cpu.showAll();
            Diagram::applyFlashTwo();
        }

        if (hasPassed(2000))
        {// Determine coin change
            Coin::determineCoinIncrease(Condition::getCond(),hmn.getHRank());
            mode = 7;
            loop_clock.restart();
            Coin::hideBettedCoins();
            if (Condition::getCond() != 2)Coin::showIncreaseCoin(); // Draw Increase coin if not a draw
        }
    }
    void loopEight()
    {
        Level::drawLevelCounter();
        hmn.drawCards();
        cpu.drawCards();
        Diagram::draw();
        Coin::draw();
        Coin::drawCoinCounter();
        Coin::drawCoinIncrease();
        if (oscillate(500) && Diagram::requiresFlash(hmn.getHRank(),cpu.getHRank()))
        {
            Diagram::applyFlashOne();
            hmn.determineDisappear(cpu.getSuit1());
            cpu.determineDisappear(hmn.getSuit1());
        }
        else
        {
            hmn.showAll();
            cpu.showAll();
            Diagram::applyFlashTwo();
        }
        if (hasPassed(2000))
        {
            if (Level::isMultipleOfFive() && Condition::getCond() == 1)
            {// Show the player has progressed to a multiple of five level only when they have won
                loop_clock.restart();
                Coin::hideIncreaseCoin();
                mode = 8;
                Sound::play5level(); // Play the special sound effect
            }
            else
            { // Otherwise check for game over first
                if (Coin::checkForGameOver())
                { // If game over, move on to next loop
                    Sound::quietMusic();
                    Sound::playGameOver();
                    hmn.showAll();
                    cpu.showAll();
                    mode = 9;
                }
                else
                { // Go back to the beginnig of the loop, with new cards
                    Coin::reset(Level::getLevel());
                    mode = 0;
                    cpu.reset(); // Reset card values
                    hmn.reset();
                }
                loop_clock.restart();
                Diagram::reset(); // Reset the diagram flashing (if applicable)
            }

        }
    }
    void loopNine()
    {
        hmn.drawCards();
        cpu.drawCards();
        Diagram::draw();
        Coin::draw();
        Coin::drawCoinCounter();
        Level::drawLevel(); // New Multiple of 5 level progressed
        if (oscillate(500) && Diagram::requiresFlash(hmn.getHRank(),cpu.getHRank()))
        {
            Diagram::applyFlashOne();
            hmn.determineDisappear(cpu.getSuit1());
            cpu.determineDisappear(hmn.getSuit1());
        }
        else
        {
            hmn.showAll();
            cpu.showAll();
            Diagram::applyFlashTwo();
        }

        if (hasPassed(2000))
        { // Reset
            Coin::reset(Level::getLevel());
            mode = 0;
            cpu.reset();
            hmn.reset();
            loop_clock.restart();
            Diagram::reset();
        }
    }
    void loopTen()
    {
        Coin::drawCoinCounter();
        Coin::draw();
        Condition::drawGameOver();
        if (hasPassed(3000))
        {
            mode = 10;
        }

    }
    void loopEleven()
    {
        Menu::drawPlayAgain();
        Menu::drawQuit();
        // Restart game or quit
        if (Mouse::isPressed() && Menu::QuitisPressed())Window::close();
        if (Mouse::isPressed() && Menu::PlayAgainisPressed())
        {
            Coin::initialise();
            Level::reset();
            mode = 0;
            cpu.reset();
            hmn.reset();
            Sound::normalMusic();
        }
    }
    void initialise()
    {
        srand(time(NULL));
        hmn.randomise();
        cpu.randomise();
        Coin::reset(Level::getLevel());
        Sound::initialise();
        Sound::playMusic();
    }
    bool oscillate(int period)
    {
        sf::Time elapsed2 = bet_clock.getElapsedTime();
        if (elapsed2.asMilliseconds()%period<period/2) return 0;
        else return 1;
    }
    bool hasPassed(int period)
    {
        sf::Time elapsed1 = loop_clock.getElapsedTime();
        if (elapsed1.asMilliseconds()<period) return 0;
        else return 1;
    }
}


