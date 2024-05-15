#ifndef PIPE_H_
#define PIPE_H_

#include "CommonFunc.h"
#include <iostream>
#include <vector>
#include <iostream>

using namespace std;

extern vector <pos> posPipe;

class pipe:LoadTexture {
private:
    const int radMin = -373 + 20;
    const int radMax = SCREEN_HEIGHT - LAND_HEIGHT - 373 - PIPE_DISTANCE - 30;
public:
    bool init();
    void Destroy();
    void Render2();
    void update();
    int width() { return getWidth(); }
    int height() { return getHeight(); }
};

#endif // PIPE_H_
