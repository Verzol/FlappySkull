#include "eagle.h"
#include "pipe.h"

bool eagle::init(bool isDark) {
    string eaglee = "resource/image/eagle.png";
    if (isDark) eaglee = "resource/image/eagle-dark.png";
    if (path_ == eaglee) {
        posEagle.getPos(75, SCREEN_HEIGHT/2 - 10);
        ahead = 0;
        angle = 0;
    }
    if (isNULL() || path_ != eaglee) {
        path_ = eaglee;
        if (Load(eaglee, 1)) {
            return true;
        }
        else return false;
    }
    return false;
}

void eagle::Destroy() {
    free();
}

void eagle::Render_() {
    Render(posEagle.x, posEagle.y, angle);
}

void eagle::fall() {
    if (die && posEagle.y < SCREEN_HEIGHT - LAND_HEIGHT - EAGLE_HEIGHT - 5) {
        if (time == 0) {
            x0 = posEagle.y;
            angle = -25;
        }
        else if (angle < 70 && time > 30) {
            angle += 4;
        }
        if (time >= 0) {
            posEagle.y = x0 + time * time * 0.2 - 7.5 * time;
            time++;
        }
    }
}

void eagle::update(int pipeWidth, int pipeHeight) {
    if (!die) {
        if (time == 0) {
            x0 = posEagle.y;
            angle = -25;
        }
        else if (angle < 70 && time > 30) {
            angle += 3;
        }

        if (time >= 0) {
            posEagle.y = x0 + time * time * 0.2 - 7.3 * time;
            time++;
        }

        if ((posEagle.x + getWidth() > posPipe[ahead].x + 6) && (posEagle.x + 6 < posPipe[ahead].x + pipeWidth) &&
            (posEagle.y + 6 < posPipe[ahead].y + pipeHeight || posEagle.y + getHeight() > posPipe[ahead].y + pipeHeight + PIPE_SPACE + 6)) {
            die = true;
        }
        else if (posEagle.x > posPipe[ahead].x + pipeWidth) {
            ahead = (ahead + 1) % TOTAL_PIPE;
            score++;
        }

        if (posEagle.y > SCREEN_HEIGHT - LAND_HEIGHT - EAGLE_HEIGHT - 5 || posEagle.y < -10) {
            die = true;
        }
    }
}

bool eagle::isScoring() {
    if(posEagle.x > posPipe[ahead].x + 65) {
        return true;
    }
    return false;
}
