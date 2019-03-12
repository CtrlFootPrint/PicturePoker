#include "graphics.h"
class diagram
{
    public:
    Sprite element[6];
    int rank_1_, rank_2_;
    int type_[6] = {0,0,0,0,0,0}; // 0 = white, 1 = green, 2 = red
    int flash_1[6] = {0,0,0,0,0,0}; // 0 = white, 1 = green, 2 = red
    int flash_2[6] = {0,0,0,0,0,0}; // 0 = white, 1 = green, 2 = red

    void setDiagram(int one, int two, int three, int four, int five, int six) // Debug function
    {
        type_[0] = one;
        type_[1] = two;
        type_[2] = three;
        type_[3] = four;
        type_[4] = five;
        type_[5] = six;
    }
    void initialise()
    {
        for (int i = 0; i<6; i++)
        {
            element[i].setCoordinates(10,167-i*16);
            if (i == 0) element[i].setLengths(20,17);
            else element[i].setLengths(20,16);
            setDiagram(0,0,0,0,0,0);
        }
    }
    void drawDiagram(sf::RenderWindow &window)
    {
        for (int i = 0; i<6; i++)
        {
            element[i].setTexture(19+i+type_[i]*6);
            element[i].draw(window);
        }
    }
    bool requireFlash(int rank_1, int rank_2)
    {
        for (int i = 0; i<6; i++)flash_1[i] = 0; // reset
        for (int i = 0; i<6; i++)flash_2[i] = 0; // reset
        rank_1_ = rank_1;
        rank_2_ = rank_2;
        if (rank_1_ == rank_2_ && rank_1_ != 0) return 1;
        else return 0;
    }
    void calcFlashOne(int majsuit_1, int majsuit_2, int minsuit_1, int minsuit_2)
    {
        if (rank_1_ == 6 || rank_1_ == 5 || rank_1_ == 3 || rank_1_ == 1)
        {
            if (majsuit_1 == majsuit_2)
            {
                flash_1[majsuit_1] = 1;
            }
            else
            {
                flash_1[majsuit_1] = 1; flash_1[majsuit_2] = 2;
            }
        }
        if (rank_1_ == 2 || rank_1_ == 4)
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
                flash_1[minsuit_1] = 1;
            }
        }
    }
    void calcFlashTwo(int majsuit_1, int majsuit_2, int minsuit_1, int minsuit_2)
    {
        if (rank_1_ == 6 || rank_1_ == 5 || rank_1_ == 3 || rank_1_ == 1)
        {
            if (majsuit_1 == majsuit_2)
            {
                flash_2[majsuit_2] = 2;
            }
        }
        if (rank_1_ == 2 || rank_1_ == 4)
        {
            if (majsuit_1 == majsuit_2 && minsuit_1 == minsuit_2)
            {
                flash_2[minsuit_1] = 2;
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
};

