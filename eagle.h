#ifndef EAGLE_H_
#define EAGLE_H_

#include "CommonFunc.h"
#include "pipe.h"

using namespace std;

class eagle:LoadTexture {
public:
    bool init(bool isDark);
    void Render_();
    void Destroy();
    void restartTime() {
        time = 0;
    }
    void fall();
    void update(int pipeWidth, int pipeHeight);
    bool isScoring();
private:
    int angle, time, x0;
    int ahead = 0;
    string path_ = "";
    pos posEagle;
};

#endif // EAGLE_H_
