#ifndef LAND_H_
#define LAND_H_

#include "CommonFunc.h"
#include <vector>

class land:LoadTexture {
public:
    bool init();
    void Destroy();
    void Render3();
    void update();
private:
    pos posLand;
};

#endif // LAND_H_
