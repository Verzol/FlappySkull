#include "GameLoop.h"
#include "CommonFunc.h"
#include <iostream>
#include <cmath>

void GameLoop::takeInput() {
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
        case SDL_QUIT:
            userInput.Type = playerInput::QUIT;
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                if (isInsideSoundIcon(mouseX, mouseY) && paused) {
                    sound.toggleSound();
                    isMuted = sound.isMute;
                }
                else if (isInsideResume(mouseX, mouseY) && !paused) {
                    userInput.Type = playerInput::PAUSE;
                    cerr << "PAUSED!" << endl;
                    paused = true;
                }
                else if (isInsideResume(mouseX, mouseY) && paused) {
                    userInput.Type = playerInput::PLAY;
                    cerr << "RESUMED!" << endl;
                    paused = false;
                }
                else if (isInsideNextButton(mouseX, mouseY) && paused) {
                    userInput.Type = playerInput::CHANGE_THEME;
                }
                else if (isInsidePauseTab(mouseX, mouseY) && !paused) {
                    userInput.Type = playerInput::PLAY;
                }
                else if (isInsideReplayTab(mouseX, mouseY) && paused) {
                    userInput.Type = playerInput::PLAY;
                    cerr << "REPLAY!" << endl;
                    paused = false;
                }
                else if (!paused) {
                    userInput.Type = playerInput::PLAY;
                }
            }
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_SPACE) {
                if (paused) {
                    userInput.Type = playerInput::PLAY;
                    paused = false;
                    cerr << "RESUMED!" << endl;
                } else {
                    userInput.Type = playerInput::PLAY;
                }
            }
            else if (event.key.keysym.sym == SDLK_p && !paused) {
                userInput.Type = playerInput::PAUSE;
                cerr << "PAUSED!" << endl;
                paused = true;
            }
            else if (event.key.keysym.sym == SDLK_p && paused) {
                userInput.Type = playerInput::PLAY;
                cerr << "RESUMED!" << endl;
                paused = false;
            }
            else if (event.key.keysym.sym == SDLK_ESCAPE) {
                userInput.Type = playerInput::QUIT;
                quit = true;
            }
            else if (event.key.keysym.sym == SDLK_t && paused) {
                userInput.Type = playerInput::CHANGE_THEME;
            }
            break;
        default:
            break;
        }
    }
}


bool GameLoop::isInsideNextButton(int mouseX, int mouseY) {
    return ((mouseX > 149 && mouseX < 149 + 13) || (mouseX > 88 && mouseX < 88 + 13)) && (mouseY > 322 && mouseY < 322 + 16);
}

bool GameLoop::isInsidePauseTab(int mouseX, int mouseY) {
    int pauseTabX = (SCREEN_WIDTH - 250) / 2;
    int pauseTabY = 230;
    int pauseTabWidth = 250;
    int pauseTabHeight = 128;
    return (mouseX >= pauseTabX && mouseX <= pauseTabX + pauseTabWidth &&
            mouseY >= pauseTabY && mouseY <= pauseTabY + pauseTabHeight);
}

bool GameLoop::isInsideResume(int mouseX, int mouseY) {
    int resumeX = SCREEN_WIDTH - 50;
    int resumeY = 20;
    int resumeWidth = 50;
    int resumeHeight = 50;

    return (mouseX >= resumeX && mouseX <= resumeX + resumeWidth &&
            mouseY >= resumeY && mouseY <= resumeY + resumeHeight);
}

bool GameLoop::isInsideReplayTab(int mouseX, int mouseY) {
    int replayTabX = (SCREEN_WIDTH - 100) / 2;
    int replayTabY = 380;
    int replayTabWidth = 100;
    int replayTabHeight = 60;
    return (mouseX >= replayTabX && mouseX <= replayTabX + replayTabWidth &&
            mouseY >= replayTabY && mouseY <= replayTabY + replayTabHeight);
}

bool GameLoop::isInsideSoundIcon(int mouseX, int mouseY) {
    int soundIconX = 107;
    int soundIconY = 267;
    int soundIconWidth = 32;
    int soundIconHeight = 24;

    return (mouseX >= soundIconX && mouseX <= soundIconX + soundIconWidth &&
            mouseY >= soundIconY && mouseY <= soundIconY + soundIconHeight);
}

GameLoop::GameLoop() {
    initGraphics();
    pipe.init();
    land.init();
    sound.init();
}

GameLoop::~GameLoop()
{
    aigle.Destroy();
    land.Destroy();
    pipe.Destroy();
    sound.Destroy();
    free();
    release();
}

void GameLoop::release() {
    SDL_DestroyWindow(g_window);
    g_window = nullptr;
    SDL_DestroyRenderer(g_renderer);
    g_renderer = nullptr;
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

bool GameLoop::initGraphics()
{
    bool success = true;

    SDL_Init(SDL_INIT_EVERYTHING);
    g_window = SDL_CreateWindow("FlappySkull",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

    if (g_window) {
        SDL_Surface* iconSurface = SDL_LoadBMP("resource/image/iconSurface.bmp");
        if (iconSurface) {
            SDL_SetWindowIcon(g_window, iconSurface);
            SDL_FreeSurface(iconSurface);
        }
        g_renderer = SDL_CreateRenderer(g_window,-1, 0);
        if (g_renderer) {
            cerr << "Window created!" << endl;
            success = true;
        }
        else {
            cerr << "Window not created!" << endl;
        }
    }
    else {
        cerr << "Window not created!" << endl;
    }

    return success;
}


void GameLoop::display() {
    SDL_RenderPresent(g_renderer);
    SDL_RenderClear(g_renderer);
}

void GameLoop::renderScore1() {
    string s = to_string(score);
    int len = s.length();
    LoadTexture image;

    vector <LoadTexture> numberImg(10);
    for (int i = 0; i < 10; i++) {
        numberImg[i].Load("resource/image/number/" + to_string(i) + ".png", 0.5);
    }

    for (int i = len - 1; i >= 0; i--) {
        int num = s[i] - '0';
        LoadTexture& currentImg = numberImg[num];

        int posX = 260 - currentImg.getWidth() * (len - i - 1) * 0.75 - 5 * (len - i - 1);
        int posY = 266;

        currentImg.Render(posX, posY);
    }
    for (int i = 0; i < 10; i++) {
        numberImg[i].free();
    }
}

void GameLoop::renderScore2() {
    string s = to_string(score);
    int len = s.length();
    LoadTexture image;

    vector <LoadTexture> numberImg(10);
    for (int i = 0; i < 10; i++) {
        numberImg[i].Load("resource/image/number/" + to_string(i) + ".png", 1);
    }

    for (int i = len - 1; i >= 0; i--) {
        int num = s[i] - '0';
        LoadTexture& currentImg = numberImg[num];

        int posX = (SCREEN_WIDTH - (currentImg.getWidth() * len + (len - 1) * 10)) / 2 + (i + 30) * i;
        int posY = 100;
        currentImg.Render(posX, posY);
    }

    for (int i = 0; i < 10; i++) {
        numberImg[i].free();
    }
}

void GameLoop::renderBestScore() {
    ifstream inFile("resource/bestScore.txt");
    if (!inFile.is_open()) {
        cerr << "Failed to open bestScore.txt" << endl;
        return;
    }
    inFile >> bestScore;
    inFile.close();

    ofstream outFile("resource/bestScore.txt", ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Failed to open bestScore.txt" << endl;
        return;
    }

    if (score > bestScore) {
        bestScore = score;
    }

    outFile << bestScore;
    outFile.close();

    string s = to_string(bestScore);
    int len = s.length();
    LoadTexture image;

    for (int i = len - 1; i >= 0; i--) {
        int num = s[i] - '0';
        image.Load("resource/image/number/" + to_string(num) + ".png", 0.5);
        int posX = 260 - image.getWidth() * (len - i - 1) * 0.75 - 5 * (len - i - 1);
        int posY = 313;
        image.Render(posX, posY);
        image.free();
    }
}

void GameLoop::renderIntro() {
    LoadTexture image;
    image.Load("resource/image/intro.png", 1);
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 180);
    image.free();
}

void GameLoop::renderBackground() {
    LoadTexture image;
    image.Load("resource/image/background.png", 1);
    image.Render(0,0);
    image.free();
}

void GameLoop::renderBackgroundNight() {
    LoadTexture image;
    image.Load("resource/image/background-night.png", 1);
    image.Render(0,0);
    image.free();
}

void GameLoop::renderLand() {
    LoadTexture image;
    image.Load("resource/image/land.png", 1);
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, SCREEN_HEIGHT - image.getHeight());
    image.free();
}

void GameLoop::resume() {
    LoadTexture image;
    image.Load("resource/image/resume.png", 1);
    image.Render(SCREEN_WIDTH - 50, 20);
    image.free();
}

void GameLoop::pause() {
    LoadTexture image;
    image.Load("resource/image/pause.png",1);
    image.Render(SCREEN_WIDTH - 50, 20);
    image.free();
}

void GameLoop::renderPauseTab() {
    LoadTexture image;
    image.Load("resource/image/pauseTab.png",1);
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 230);
    image.free();
}

void GameLoop::Theme1() {
    LoadTexture image;
    image.Load("resource/image/eagle.png", 1);
    image.Render(103, 315);
    image.free();
}

void GameLoop::Theme2() {
    LoadTexture image;
    image.Load("resource/image/eagle-dark.png", 1);
    image.Render(103,315);
    image.free();
}

void GameLoop::nextButton() {
    LoadTexture image;
    image.Load("resource/image/nextRight.png", 1);
    image.Render(149,322);
    image.Load("resource/image/nextLeft.png", 1);
    image.Render(88,322);
    image.free();
}

bool GameLoop::changeTheme() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (((x > 149 && x < 149+13)  || (x > 88 && x < 88 + 13)) && (y > 322 && y < 322 + 16)) {
        return true;
    }
    return false;
}

void GameLoop::renderGameOver() {
    LoadTexture image;
    image.Load("resource/image/gameOver.png", 1);
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 150);
    image.free();
}

void GameLoop::renderMedal() {
    LoadTexture image;
    if (score > 0) {
        image.Load("resource/image/medal.png", 1);
        image.Render(82, 290);
    }
    image.free();
}

void GameLoop::replay() {
    LoadTexture image;
    image.Load("resource/image/replay.png", 1);
    image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 380);
    image.free();
}

bool GameLoop::checkReplay() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (((mouseX > (SCREEN_WIDTH - 100)/2 && mouseX < (SCREEN_WIDTH + 100) / 2 && mouseY > 380 && mouseY < 380 + 60))) {
        return true;
    }
    else if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE && isDie())) {
        return true;
    }
    return false;
}

void GameLoop::Restart() {
    die = false;
    score = 0;
    aigle.restartTime();
}







