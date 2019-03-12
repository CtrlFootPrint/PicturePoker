#include "graphics.h"
int whoWins (int rank_1, int rank_2,
int majsuit_1, int majsuit_2, int minsuit_1, int minsuit_2)
// 0 - Computer wins, 1 - Player wins, 2 - Same rank or draw
{
    if (rank_1 < rank_2) return 0;
    else if (rank_1 > rank_2) return 1;
    else if (rank_1 == rank_2)
    {
        if (rank_1 == 0) return 2;
        else if (rank_1 == 6 || rank_1 == 5 || rank_1 == 3 || rank_1 == 1  )
        {
            if (majsuit_1<majsuit_2) return 0;
            else if (majsuit_1>majsuit_2) return 1;
            else return 2;
        }
        else if (rank_1 == 4 || rank_1 == 2)
        {

            if (majsuit_1<majsuit_2) return 0;
            else if (majsuit_1>majsuit_2) return 1;
            else if (minsuit_1<minsuit_2) return 0;
            else if (minsuit_1>minsuit_2) return 1;
            else return 2;
        }
    }
}
void drawWhoWinsGfx(sf::RenderWindow &window, int status)
{
    Sprite whowins_gfx; // Sprite used to draw rank
    if (status == 0) // Too bad
    {
        whowins_gfx.setCoordinates(59,81);
        whowins_gfx.setLengths(175,30);
    }
    if (status == 1) // You win!
    {
        whowins_gfx.setCoordinates(59,80);
        whowins_gfx.setLengths(177,32);
    }
    if (status == 2) // Draw
    {
        whowins_gfx.setCoordinates(94,81);
        whowins_gfx.setLengths(99,30);
    }
        whowins_gfx.setTexture(16+status);
        whowins_gfx.draw(window);
}
