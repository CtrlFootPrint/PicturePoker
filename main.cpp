// TODO LIST:
// Correctly split headers into .cpp and .h files, separating definitions with declarations
// Implement coins, and (eventually) levels
// Make computer AI... basically make it able to swap cards random way
//...
// Improve animation

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "cards.h"
#include "condition.h"
#include "graphics.h"
#include "diagram.h"
#include <iostream>
bool mouse_pressed = 0;
bool box_on = 1;
bool rank_gfx_on = 0;
bool whowins_gfx_on = 0;
bool bet_on = 1;
bool bet_c = 0;
int g_counter = 0; // General counter
int mode = 0;
int status = 0;
bool waitfor(sf::Clock clock, int period);
bool oscillate(sf::Clock clock, int period);
bool flash = 0;
int main()
{
    sf::Clock clock; // Initialise clock
    sf::Clock bet_clock; // Initialise clock
    srand (time(NULL)); // Initialise seed
    Cardset hmn(128,112,0);
    Cardset cpu(16,64,1);
    hmn.initialise();
    diagram Diagram;
    Diagram.initialise();
    cpu.initialise();
    initialise(); // Initialise textures
    sf::RenderWindow window(sf::VideoMode(256,192), "Picture Poker"); // Initialise window with width, length and name
    while (window.isOpen()) // Start game loop
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close(); // close window when X is pressed
            }
        }
		window.clear();
		window.draw(bb); // draw background
        box.setTexture(boxs); // put texture on box, which depends on any cards that may have been selected
        bet.setTexture(37+bet_c);
        if (bet_on) bet.draw(window);
        if (box_on)box.draw(window); // draw box
        Diagram.drawDiagram(window);
        hmn.drawCards(window); // draw the player's Cards
        cpu.drawCards(window); // draw the cpu's Cards
        if (rank_gfx_on)hmn.drawRankGfx(window); // Draw player hand rank
        if (rank_gfx_on)cpu.drawRankGfx(window); // Draw cpu hand rank
        if (whowins_gfx_on)drawWhoWinsGfx(window,status);

		window.display(); // update the whole window

        // START MODES --------------------------------

        if (mode == 0){ // Take input from user
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // if mouse is pressed
        {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window); // get position of the mouse on screen
            if (mouse_pressed == 0) //if mouse has been pressed for first interval
            {
                mouse_pressed = 1; // to prevent this loop from running again
                hmn.highlightApplicableCards(localPosition); // check if cards have been pressed
                if (box.isPressed(localPosition))
                {
                    hmn.hideApplicableCards();
                    mode = 1; // Change mode
                    box_on = 0; // Hide box graphic
                    bet_on = 0;
                }
                if (hmn.NoCardSelected())boxs = 0; // If there are no cards selected, make the box say Hold
                else boxs = 1; // Otherwise make it say Draw
            }
        }
        else mouse_pressed = 0;
        if ( oscillate(bet_clock,500) ) bet_c = 0;
        else bet_c = 1;
        }
        else if (mode == 1){ // Show the cards that have been selected flipped.

            clock.restart();
            while (waitfor(clock,500)){}; // wait for 500 milliseconds.
            hmn.switchCards(); // switch cards with new values
            hmn.unhideCards();
            mode = 2; // Next mode
            boxs = 0; // Make box say hold
            //cpu.setCards(3,3,3,0,0);
            //hmn.setCards(3,3,3,1,1);
        }
        else if (mode == 2) // Switch the cards that have been selected, unflipping them
        {
            hmn.countCards();
            hmn.arrangeCards();
            hmn.applyArrangement();
            cpu.countCards();
            cpu.arrangeCards();
            cpu.applyArrangement();
            cpu.unhideCards();
            rank_gfx_on = 1; // Draw rank graphic
            clock.restart();
            while (waitfor(clock,500)){}; // wait for a bitwhowins_gfx
            mode = 3;
        }
        else if (mode == 3) // Rearrange cards to show the rank of the hand
        {
            flash = Diagram.requireFlash( hmn.getHRank(),cpu.getHRank() );
            if ( flash )
            {
                Diagram.calcFlashOne(cpu.getSuit1(),hmn.getSuit1(),cpu.getSuit2(),hmn.getSuit2());
                Diagram.calcFlashTwo(cpu.getSuit1(),hmn.getSuit1(),cpu.getSuit2(),hmn.getSuit2());

            }
            status = whoWins(hmn.getHRank(),cpu.getHRank(),hmn.getSuit1(),cpu.getSuit1(),hmn.getSuit2(),cpu.getSuit2());
            clock.restart();
            while (waitfor(clock,700)){}; // wait for a bit

            mode = 4;
            if (flash)
            {
                Diagram.applyFlashOne();
                hmn.determineDisappear(cpu.getSuit1());
                cpu.determineDisappear(hmn.getSuit1());
            }
            std::cout << hmn.getSuit1() << "\n";
            std::cout << cpu.getSuit1() << "\n";
        }
        else if (mode == 4)
        {
            g_counter++;
            if (flash)
            {
                if (g_counter%2 == 1)
                {
                    Diagram.applyFlashTwo();
                    hmn.applyDisappear(0,0,0,0,0);
                    cpu.applyDisappear(0,0,0,0,0);
                }
                else
                {
                    Diagram.applyFlashOne();
                    hmn.determineDisappear(cpu.getSuit1());
                    cpu.determineDisappear(hmn.getSuit1());
                }
            }
            //while (waitfor(clock,3000)){}; // wait for a bit
            sf::sleep(sf::milliseconds(300));
            if (g_counter > 3)
            {
            whowins_gfx_on = 1;
             rank_gfx_on = 0; // Don't draw rank graphic any more.
            }
            if (g_counter == 14)
            {
                g_counter = 0;
                mode = 0;
                box_on = 1; // box back on
                bet_on = 1; // bet back on
                hmn.initialise(); // New hand
                cpu.initialise(); // New hand
                whowins_gfx_on = 0;
                Diagram.initialise();
            }
        }

        }

    return 0;

}
bool waitfor(sf::Clock clock, int period)
{
    sf::Time elapsed1 = clock.getElapsedTime();
    if (elapsed1.asMilliseconds()>period) return 0;
    else return 1;
}
bool oscillate(sf::Clock clock, int period)
{
    sf::Time elapsed2 = clock.getElapsedTime();
    if (elapsed2.asMilliseconds()%period<period/2) return 0;
    else return 1;
}
