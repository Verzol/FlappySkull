#ifndef COMMONFUNC_H_
#define COMMONFUNC_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

using namespace std;

class pos {
public:
    int x, y, angle, state;
    void getPos(const int x, const int y);
};

class LoadTexture {
public:
    LoadTexture();
    ~LoadTexture();

    bool isNULL();

    bool Load(string path, float scale);

    int getWidth();
    int getHeight();

    void free();
    void Render(int x, int y, int angle = 0, SDL_Rect* clip = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
public:
    SDL_Texture* _texture;
    int Width1;
    int Height1;

public:
    static SDL_Window* g_window;
    static SDL_Event event;
    static SDL_Renderer* g_renderer;

    static bool quit;
    static bool die;
    static int score;

    static const int SCREEN_WIDTH = 350;
    static const int SCREEN_HEIGHT = 625;
    static const int PIPE_SPACE = 150;
    static const int TOTAL_PIPE = 4;
    static const int PIPE_DISTANCE = 195;
    static const int LAND_HEIGHT = 140;
    static const int EAGLE_HEIGHT = 35;
    static const int EAGLE_WIDTH = 50;

};
#endif // COMMONFUNC_H_
