#include "graphics.h"

    Sprite::Sprite()
    {
        //
    };
    Sprite::Sprite(int lengthx, int lengthy, int ID)
    {
        ID_ = ID;
        lengthx_ = lengthx;
        lengthy_ = lengthy;
    }
    void Sprite::draw()
    {
        sprite_.setTexture(Texture::getRef(ID_));
        sprite_.setPosition(x_,y_);
        Window::drawSprite(sprite_);
    }
    void Sprite::setCoordinates (int x, int y)
    {
        x_ = x;
        y_ = y;
    }
    void Sprite::setLengths (int x, int y)
    {
        lengthx_ = x;
        lengthy_ = y;
    }
    void Sprite::setTexture (int ID)
    {
        ID_ = ID;
    }
    void Sprite::displaceX (int dis)
    {
        x_+= dis;
    }
    void Sprite::displaceY (int dis)
    {
        y_+= dis;
    }
    bool Sprite::isPressed () // To be used only after mouse has been pressed
    {
        if (Window::hasFocus() == 0) return 0;
        if ( (Mouse::getXPos() >=x_ && Mouse::getXPos() <= (x_+lengthx_-1))
            && (Mouse::getYPos() >=y_ && Mouse::getYPos() <= (y_+lengthy_-1)) )
            //&& Window::hasFocus() == 1 )
        {
            return 1;
        }
        else return 0;


    }



