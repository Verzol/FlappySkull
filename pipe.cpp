#include "pipe.h"

vector <pos> posPipe;

bool pipe::init() {
    posPipe.clear();

    if (isNULL()) {
        if (!Load("resource/image/pipe.png", 1)) {
            return false;
        }
    }
    for (int i = 0; i < TOTAL_PIPE; i++) {
        pos temp;
        temp.getPos(SCREEN_WIDTH + i * PIPE_DISTANCE + 350, (rand() % (radMax - radMin + 1)) + radMin);
        posPipe.push_back(temp);
    }
    return true;
}

void pipe::Destroy() {
    free();
}

void pipe::Render2() {
    for (int i = 0; i < TOTAL_PIPE; i++) {
        if (posPipe[i].x > -getWidth() && posPipe[i].x <= SCREEN_WIDTH) {
            Render(posPipe[i].x, posPipe[i].y, 180);
            Render(posPipe[i].x, posPipe[i].y + getHeight() + PIPE_SPACE);
        }
    }
}
void pipe::update() {
    if (!die) {
        const double pipeSpeed = 3;
        for (int i = 0; i < TOTAL_PIPE; i++) {
            if (posPipe[i].x < -getWidth()) {
                posPipe[i].y = (rand() % (radMax - radMin + 1)) + radMin;
                posPipe[i].x = posPipe[(i + TOTAL_PIPE - 1) % TOTAL_PIPE].x + PIPE_DISTANCE;
            }
            else {
                posPipe[i].x -= pipeSpeed;
            }
        }
    }
}
