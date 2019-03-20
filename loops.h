#ifndef LOOP_H
#define LOOP_H
#include "graphics.h"
#include "card.h"
#include "othergfx.h"
#include "coin.h"
#include "mouse.h"
#include "sound.h"
#include "window.h"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
namespace mainloop
{
    void run();
    void loopOne();
    void loopTwo();
    void loopThree();
    void loopFour();
    void loopFive();
    void loopSix();
    void loopSeven();
    void loopEight();
    void loopNine();
    void loopTen();
    void loopEleven();
    void initialise();
    int getMode();
    bool oscillate(int period);
    bool hasPassed(int period);
}
#endif // LOOP_H
