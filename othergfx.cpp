#include "othergfx.h"
namespace Box
{
    namespace
    {
        bool box_gfx = 0; // Determines text: 0 = hold, 1 = draw
        Sprite box_sprite;
    }
    void draw()
    {
        box_sprite.setTexture(box_gfx);
        box_sprite.setCoordinates(56,72);
        box_sprite.setLengths(144,32);
        box_sprite.draw();
    }
    void setToDraw()
    {
        box_gfx = 1;
    }
    void setToHold()
    {
        box_gfx = 0;
    }
    bool isPressed()
    {
        return box_sprite.isPressed();
    }
}

namespace Bet
{
    namespace
    {
        bool bet_gfx = 0; // Determines flash: 0 = yellow, 1 = orange
        Sprite bet_sprite;
    }
    void draw()
    {
        bet_sprite.setTexture(37+bet_gfx);
        bet_sprite.setCoordinates(3,31);
        bet_sprite.setLengths(35,35);
        bet_sprite.draw();
    }
    void setToFlash0()
    {
        bet_gfx = 0;
    }
    void setToFlash1()
    {
        bet_gfx = 1;
    }
    bool isPressed()
    {
        return bet_sprite.isPressed();
    }
}

namespace Diagram
{
    namespace
    {
        Sprite element[6];
        int type_[6] = {0,0,0,0,0,0}; // 0 = white, 1 = green, 2 = red
        int flash_1[6] = {0,0,0,0,0,0}; // 0 = white, 1 = green, 2 = red
        int flash_2[6] = {0,0,0,0,0,0}; // 0 = white, 1 = green, 2 = red
    }
    void draw ()
    {
        for (int i = 0; i<6; i++)
        {
            element[i].setCoordinates(10,167-i*16);
            if (i == 0) element[i].setLengths(20,17);
            else element[i].setLengths(20,16);
            element[i].setTexture(19+i+type_[i]*6);
            element[i].draw();
        }
    }
    void setDiagram(int one, int two, int three, int four, int five, int six) // Debug function
    {
        type_[0] = one;
        type_[1] = two;
        type_[2] = three;
        type_[3] = four;
        type_[4] = five;
        type_[5] = six;
    }
    bool requiresFlash(int rank_1, int rank_2)
    {
        if (rank_1 == rank_2 && rank_1 != 0) return 1;
        else return 0;
    }
    void setFlashes(int rank, int majsuit_1, int majsuit_2, int minsuit_1, int minsuit_2)
    {
        if (rank == 6 || rank == 5 || rank == 3 || rank == 1)
        {
            if (majsuit_1 == majsuit_2)
            {
                flash_1[majsuit_1] = 1;
                flash_2[majsuit_2] = 2;
            }
            else
            {
                flash_1[majsuit_1] = 1; flash_1[majsuit_2] = 2;
            }
        }
        if (rank == 2 || rank == 4)
        {
            if (majsuit_1 != majsuit_2)
            {
                flash_1[majsuit_1] = 1;
                flash_1[majsuit_2] = 2;
            }
            else  if (majsuit_1 == majsuit_2 && minsuit_1 != minsuit_2)
            {
                flash_1[minsuit_1] = 1; flash_1[minsuit_2] = 2;

            }
            else
            {
                flash_1[minsuit_1] = 1; flash_2[minsuit_2] = 2;
            }
        }
    }
    void applyFlashOne()
    {
        setDiagram(flash_1[0],flash_1[1],flash_1[2],flash_1[3],flash_1[4],flash_1[5]);
    }
    void applyFlashTwo()
    {
        setDiagram(flash_2[0],flash_2[1],flash_2[2],flash_2[3],flash_2[4],flash_2[5]);
    }
    void reset()
    {
        for (int i = 0; i<6; i++)
        {
            type_[i] = 0;
            flash_1[i] = 0;
            flash_2[i] = 0;
        }
    }
}
namespace Condition
{
    namespace
    {
        int cond_gfx = 0; // 0 - Too Bad, 1 - You Win!, 2 - Draw
    }
    void draw()
    {
        Sprite cond_sprite;
        if (cond_gfx == 0) // Too bad
        {
            cond_sprite.setCoordinates(59,81);
            cond_sprite.setLengths(175,30);
        }
        if (cond_gfx == 1) // You win!
        {
            cond_sprite.setCoordinates(59,80);
            cond_sprite.setLengths(177,32);
        }
        if (cond_gfx == 2) // Draw
        {
            cond_sprite.setCoordinates(94,81);
            cond_sprite.setLengths(99,30);
        }
        cond_sprite.setTexture(16+cond_gfx);
        cond_sprite.draw();
    }
    void setToLose()
    {
        cond_gfx = 0;
    }
    void setToWin()
    {
        cond_gfx = 1;
    }
    void setToDraw()
    {
        cond_gfx = 2;
    }
    void whoWins(int rank_1, int rank_2, int majsuit_1, int majsuit_2, int minsuit_1, int minsuit_2)
    {
        if (rank_1 < rank_2) setToLose();
        else if (rank_1 > rank_2) setToWin();
        else if (rank_1 == rank_2)
        {
            if (rank_1 == 0) setToDraw();
            else if (rank_1 == 6 || rank_1 == 5 || rank_1 == 3 || rank_1 == 1  )
            {
                if (majsuit_1<majsuit_2) setToLose();
                else if (majsuit_1>majsuit_2) setToWin();
                else setToDraw();
            }
            else if (rank_1 == 4 || rank_1 == 2)
            {

                if (majsuit_1<majsuit_2) setToLose();
                else if (majsuit_1>majsuit_2) setToWin();
                else if (minsuit_1<minsuit_2) setToLose();
                else if (minsuit_1>minsuit_2) setToWin();
                else setToDraw();
            }
        }
    }
    int getCond()
    {
        return cond_gfx;
    }
    void drawGameOver()
    {
        Sprite cond_sprite;
        cond_sprite.setCoordinates(18,81);
        cond_sprite.setLengths(217,29);
        cond_sprite.setTexture(92);
        cond_sprite.draw();

    }
}

Numbers::Numbers(int x, int y)
{
    x_ = x;
    y_ = y;
}

void Numbers::draw(int num)
{

    if (num < 10)
    {
        Sprite num_gfx[1];
        num_gfx[0].setTexture(40+num);
        num_gfx[0].setCoordinates(x_,y_);
        num_gfx[0].draw();
    }
    else if (num < 100)
    {
        Sprite num_gfx[2];
        int ones = num%10;
        int tens = num/10;
        num_gfx[0].setTexture(40+ones);
        num_gfx[0].setCoordinates(x_+16,y_);
        num_gfx[0].draw();
        num_gfx[1].setTexture(40+tens);
        num_gfx[1].setCoordinates(x_,y_);
        num_gfx[1].draw();

    }
    else if (num < 1000)
    {
        Sprite num_gfx[3];
        int ones = num%10;
        int tens = (num/10)%10;
        int hundreds = num/100;
        num_gfx[0].setTexture(72+ones);
        num_gfx[0].setCoordinates(x_+13,y_);
        num_gfx[0].draw();
        num_gfx[1].setTexture(72+tens);
        num_gfx[1].setCoordinates(x_+5,y_);
        num_gfx[1].draw();
        num_gfx[2].setTexture(72+hundreds);
        num_gfx[2].setCoordinates(x_-3,y_);
        num_gfx[2].draw();

    }
    else if (num < 10000)
    {
        Sprite num_gfx[4];
        int ones = num%10;
        int tens = (num/10)%10;
        int hundreds = (num/100)%10;
        int thousands = num/1000;
        num_gfx[0].setTexture(72+ones);
        num_gfx[0].setCoordinates(x_+21,y_);
        num_gfx[0].draw();
        num_gfx[1].setTexture(72+tens);
        num_gfx[1].setCoordinates(x_+13,y_);
        num_gfx[1].draw();
        num_gfx[2].setTexture(72+hundreds);
        num_gfx[2].setCoordinates(x_+5,y_);
        num_gfx[2].draw();
        num_gfx[3].setTexture(72+thousands);
        num_gfx[3].setCoordinates(x_-3,y_);
        num_gfx[3].draw();
    }
}
void Numbers::drawSigned(int num)
{

    if (num>0)
    {
        if (num < 10)
        {
            Sprite num_gfx[2];
            num_gfx[0].setTexture(71);
            num_gfx[0].setCoordinates(x_,y_);
            num_gfx[0].draw();
            num_gfx[1].setTexture(61+num);
            num_gfx[1].setCoordinates(x_+16,y_);
            num_gfx[1].draw();
        }
        else if (num < 100)
        {
            Sprite num_gfx[3];
            num_gfx[0].setTexture(71);
            num_gfx[0].setCoordinates(x_,y_);
            num_gfx[0].draw();
            int ones = num%10;
            int tens = num/10;
            num_gfx[1].setTexture(61+ones);
            num_gfx[1].setCoordinates(x_+32,y_);
            num_gfx[1].draw();
            num_gfx[2].setTexture(61+tens);
            num_gfx[2].setCoordinates(x_+16,y_);
            num_gfx[2].draw();
        }
    }
    else if (num<0)
    {
        Sprite num_gfx[2];
        num_gfx[0].setTexture(60);
        num_gfx[0].setCoordinates(x_,y_);
        num_gfx[0].draw();
        num_gfx[1].setTexture(50-num); // -num to convert from -ve to +ve
        num_gfx[1].setCoordinates(x_+16,y_);
        num_gfx[1].draw();
    }
}
void Numbers::drawLittleRed(int num)
{

    if (num < 10)
    {
        Sprite num_gfx[1];
        num_gfx[0].setTexture(82+num);
        num_gfx[0].setCoordinates(x_+4,y_);
        num_gfx[0].draw();

    }
    else if (num < 100)
    {
        Sprite num_gfx[2];
        int ones = num%10;
        int tens = (num/10)%10;
        num_gfx[0].setTexture(82+ones);
        num_gfx[0].setCoordinates(x_+8,y_);
        num_gfx[0].draw();
        num_gfx[1].setTexture(82+tens);
        num_gfx[1].setCoordinates(x_,y_);
        num_gfx[1].draw();

    }
}
namespace Menu
{
    namespace
    {
        Sprite PlayAgain_gfx;
        Sprite Quit_gfx;
    }
    void drawPlayAgain()
    {
        PlayAgain_gfx.setTexture(93);
        PlayAgain_gfx.setCoordinates(56,92);
        PlayAgain_gfx.setLengths(147,35);
        PlayAgain_gfx.draw();
    }
    void drawQuit()
    {
        Quit_gfx.setTexture(94);
        Quit_gfx.setCoordinates(56,140);
        Quit_gfx.setLengths(147,35);
        Quit_gfx.draw();
    }
    bool PlayAgainisPressed()
    {
        PlayAgain_gfx.setLengths(147,35);
        return PlayAgain_gfx.isPressed();
    }
    bool QuitisPressed()
    {
        Quit_gfx.setLengths(147,35);
        return Quit_gfx.isPressed();
    }
}
