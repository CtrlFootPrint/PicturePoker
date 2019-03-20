#ifndef OTHERGFX_H
#define OTHERGFX_H
#include "graphics.h"
#include <iostream>

namespace Box
{

    void draw();
    void setToDraw();
    void setToHold();
    bool isPressed();
}
namespace Bet
{
    void draw();
    void setToFlash0();
    void setToFlash1();
    bool isPressed();
}
namespace Diagram
{
    void draw();
    void setDiagram(int one, int two, int three, int four, int five, int six);
    bool requiresFlash(int rank_1, int rank_2);
    void setFlashes(int rank, int majsuit_1, int majsuit_2, int minsuit_1, int minsuit_2);
    void applyFlashOne();
    void applyFlashTwo();
    void reset();

}
namespace Condition
{
    void draw();
    void setToLose();
    void setToWin();
    void setToDraw();
    void whoWins(int rank_1, int rank_2, int majsuit_1, int majsuit_2, int minsuit_1, int minsuit_2);
    int getCond();
    void drawGameOver();
}

class Numbers
{
    int x_, y_; // Where to draw the number
    public:
    Numbers(int x, int y);
    void draw(int num);
    void drawLittleRed(int num);
    void drawSigned(int num);
};

namespace Menu
{
    void drawPlayAgain();
    void drawQuit();
    bool PlayAgainisPressed();
    bool QuitisPressed();
}

#endif //   OTHERGFX_H
