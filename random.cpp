#include "random.h"
namespace Random
{
    int getRandom(int from, int to)
    {
        int randnum = from + rand()%to;
        return randnum;
    }
}
