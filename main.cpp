#include <iostream>
#include "CommonFunc.h"
#include "GameLoop.h"
#include "mixer.h"

using namespace std;

void handleDeath(GameLoop& g, bool& isMenu, bool& isDark);
void handleGameplay(GameLoop& g, bool& isPause, bool& isDark, bool& isSound);
void capFrameRate(Uint32 frameStart, int frameDelay);

mixer soundManager;

int main(int argc, char** argv)
{
    GameLoop g;
    bool isMenu = false;
    bool isPause = false;
    bool isDark = false;
    bool isSound = true;

    soundManager.init();
    static int FPS = 75;
    if (isDark == true) {
        FPS = 90;
    }
    else {
        FPS = 75;
    }
    int frameDelay = 1000 / FPS;

    soundManager.playbgMusic();

    while (!g.isQuit())
    {
        Uint32 frameStart = SDL_GetTicks();

        handleDeath(g, isMenu, isDark);
        handleGameplay(g, isPause, isDark, isSound) ;

        g.takeInput();
        if (g.userInput.Type == GameLoop::playerInput::CHANGE_THEME)
        {
            soundManager.playClick();
            isDark = !isDark;
            g.aigle.init(isDark);
            g.userInput.Type = GameLoop::playerInput::NONE;
        }

        capFrameRate(frameStart, frameDelay);
    }

    soundManager.stopbgMusic();

    return 0;
}

void handleDeath(GameLoop& g, bool& isMenu, bool& isDark)
{
    bool wasAlive = !g.isDie();

    if (g.isDie() && !wasAlive)
    {
        if (isMenu) {
            soundManager.playHit();
            g.aigle.Render_();
        }
        g.userInput.Type = GameLoop::playerInput::NONE;

        while(g.isDie() && !g.isQuit())
        {
            g.takeInput();

            if (isMenu && (g.userInput.Type == GameLoop::playerInput::PLAY || g.userInput.Type == GameLoop::playerInput::REPLAY))
            {
                if (g.checkReplay() || g.userInput.Type == GameLoop::playerInput::REPLAY)
                {
                    isMenu = false;
                    g.userInput.Type = GameLoop::playerInput::NONE;
                    break;
                }
                g.userInput.Type = GameLoop::playerInput::NONE;
            }

            if (!isDark)
                g.renderBackground();
            else
                g.renderBackgroundNight();

            g.pipe.Render2();
            g.land.Render3();

            if (isMenu)
            {
                g.aigle.Render_();
                g.aigle.fall();
                g.renderGameOver();
                g.renderMedal();
                g.renderScore1();
                g.renderBestScore();
                g.replay();
            }
            else
            {
                g.pipe.init();
                g.aigle.init(isDark);
                g.aigle.Render_();
                g.renderIntro();

                if (g.userInput.Type == GameLoop::playerInput::PLAY)
                {
                    g.Restart();
                    isMenu = true;
                    g.userInput.Type = GameLoop::playerInput::NONE;
                }

                g.land.update();
            }

            g.display();
        }
        g.pipe.init();
    }
}

void handleGameplay(GameLoop& g, bool& isPause, bool& isDark, bool& isSound)
{
    g.takeInput();

    if (g.userInput.Type == GameLoop::playerInput::PAUSE)
    {
        soundManager.playClick();
        isPause = !isPause;
        g.userInput.Type = GameLoop::playerInput::NONE;
    }

    if (isPause == false && g.userInput.Type == GameLoop::playerInput::PLAY)
    {
        soundManager.playJump();
        g.aigle.restartTime();
        g.userInput.Type = GameLoop::playerInput::NONE;
    }

    if (isPause)
    {
        g.takeInput();
        if (g.userInput.Type == GameLoop::playerInput::PLAY)
        {
            soundManager.playJump();
            isPause = false;
            g.userInput.Type = GameLoop::playerInput::NONE;
        }
    }

    if (!isDark) g.renderBackground();
    else g.renderBackgroundNight();

    g.pipe.Render2();
    g.land.Render3();
    g.aigle.Render_();
    g.renderScore2();

    if (!isPause && !g.isDie())
    {
        g.aigle.update(g.getPipeWidth(), g.getPipeHeight());
        g.pipe.update();
        g.land.update();
        g.pause();

        if (g.aigle.isScoring()) {
            soundManager.playPoint();
        }
    }
    else
    {
        g.resume();
        g.renderPauseTab();
        g.renderScore1();
        g.renderBestScore();
        g.replay();
        soundManager.renderSound();
        if (!isDark) g.Theme1(); else g.Theme2();
        g.nextButton();

        if (g.userInput.Type == GameLoop::playerInput::PLAY)
        {
            if (g.checkReplay())
            {
                isPause = false;
            }
            else if (soundManager.checkSound()) {
                isSound = !isSound;
            }
            else if (g.changeTheme())
            {
                soundManager.playClick();
                isDark = !isDark;
                g.aigle.init(isDark);
            }

            g.userInput.Type = GameLoop::playerInput::NONE;
        }
    }

    g.display();
}

void capFrameRate(Uint32 frameStart, int frameDelay)
{
    int frameTime = SDL_GetTicks() - frameStart;

    if (frameDelay > frameTime)
    {
        SDL_Delay(frameDelay - frameTime);
    }
}
