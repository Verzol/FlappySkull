#ifndef GAMELOOP_H_
#define GAMELOOP_H_

#include "eagle.h"
#include "pipe.h"
#include "land.h"
#include "mixer.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class GameLoop:LoadTexture {
public:
    struct playerInput {
        static const int QUIT = 0;
        static const int PLAY = 1;
        static const int NONE = 2;
        static const int PAUSE = 3;
        static const int CHANGE_THEME = 4;
        static const int REPLAY = 5;
        int Type;
    };
    playerInput userInput;
    eagle aigle;
    pipe pipe;
    mixer sound;
    land land;
    bool isDarkTheme;
    bool isMuted;

public:
    GameLoop();
    ~GameLoop();

    bool initGraphics();
    bool isQuit() {
        return quit;
    }
    bool isDie() {
        return die;
    }
    int getPipeWidth() {return pipe.width();}
    int getPipeHeight() {return pipe.height();}

    void takeInput();

    void display();

    void release();

    void renderScore1();
    void renderScore2();
    void renderBestScore();

    void renderIntro();

    void renderBackground();
    void renderBackgroundNight();

    void renderLand();

    void resume();
    void pause();

    void renderPauseTab();

    void Theme1();
    void Theme2();

    void nextButton();

    bool changeTheme();

    void renderGameOver();
    void renderMedal();

    void replay();

    bool checkReplay();

    void Restart();

    bool isInsideNextButton(int x, int y);
    bool isInsidePauseTab(int x, int y);
    bool isInsideResume(int x, int y);
    bool isInsideReplayTab(int x, int y);
    bool isInsideSoundIcon(int x, int y);

private:
    const float scaleNum = 1;
    int bestScore;
    bool paused = false;
};

#endif // GAMELOOP_H_
