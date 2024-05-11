#include "CommonFunc.h"

bool LoadTexture::quit = false;
bool LoadTexture::die = true;
int LoadTexture::score = 0;
SDL_Window* LoadTexture::g_window = nullptr;
SDL_Renderer* LoadTexture::g_renderer = nullptr;
SDL_Event LoadTexture::event;


LoadTexture::LoadTexture() {
    _texture = nullptr;
}

LoadTexture::~LoadTexture() {
    free();
}

int LoadTexture::getWidth() {
    return Width1;
}

int LoadTexture::getHeight() {
    return Height1;
}

void LoadTexture::Render(int x, int y, int angle, SDL_Rect* clip, SDL_RendererFlip flip) {
    SDL_Rect Rec_Render = {x, y, Width1, Height1};

    if (clip != nullptr) {
        Rec_Render.w = clip -> w;
        Rec_Render.h = clip -> h;
    }

    SDL_RenderCopyEx(g_renderer,_texture, clip, &Rec_Render, angle, NULL, flip);
}

void LoadTexture::free() {
    if (_texture != NULL) {
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
        Width1 = 0;
        Height1 = 0;
    }
}

bool LoadTexture::Load(string path, float scale)
{
	free();

	SDL_Surface* loadd = IMG_Load(path.c_str());
	if( loadd == NULL )
	{
		cerr << "Unable to load image";
		return false;
	}
	else
	{
		SDL_SetColorKey(loadd, SDL_TRUE, SDL_MapRGB(loadd->format, 0x00, 0xFF, 0xFF ));

        _texture = SDL_CreateTextureFromSurface(g_renderer, loadd);
		if( _texture == NULL )
		{
			cerr << "Unable to load image";
			return false;
		}
		else
		{
			Width1 = (loadd->w) * scale;
			Height1 = (loadd->h) * scale;
		}

		SDL_FreeSurface(loadd);
	}
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	return _texture != NULL;

}

bool LoadTexture::isNULL() {
    if (_texture != nullptr) return false;
    return true;
}

void pos::getPos(int x, int y) {
    this->x = x;
    this->y = y;
}

