#include "mixer.h"
#include <iostream>
#include <string>

bool mixer::init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        cerr << "SDL_mixer cannot initialize!" << endl;
    }
    else {
        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                cerr << "SDL_mixer cannot initialize!" << endl;
                success = false;
            }

        point = Mix_LoadWAV(point_path.c_str());
        if (point == nullptr) {
            cerr << "Failed to load pointing sound" << endl;
            success = false;
        }

        click = Mix_LoadWAV(click_button.c_str());
        if (click == nullptr) {
            cerr << "Failed to load clicking sound" << endl;
            success = false;
        }

        bgMusic = Mix_LoadMUS(bgMusic_path.c_str());
        if (bgMusic == nullptr) {
            cerr << "Failed to load background music" << endl;
            success = false;
        }

        jump = Mix_LoadWAV(jump_path.c_str());
        if (jump == nullptr) {
            cerr << "Failed to load jumping sound" << endl;
            success = false;
        }
        hit = Mix_LoadWAV(hit_path.c_str());
        if (hit == nullptr) {
            cerr << "Failed to load hit sound" << endl;
        }
        isPlay = true;
    }
    return success;
}

void mixer::Destroy() {
    free();

    Mix_FreeMusic(bgMusic);
    bgMusic = nullptr;
    Mix_FreeChunk(jump);
    jump = nullptr;
    Mix_FreeChunk(hit);
    hit = nullptr;
    Mix_FreeChunk(point);
    point = nullptr;
    Mix_FreeChunk(click);
    click = nullptr;
    Mix_Quit();
}

void mixer::playbgMusic() {
    if (isPlay) {
        Mix_HaltMusic();
        Mix_PlayMusic(bgMusic, 1);
    }
}

void mixer::playHit() {
    if (isPlay) {
        Mix_PlayChannel(-1, hit, 0);
    }
}

void mixer::playJump() {
    if (isPlay) {
        Mix_PlayChannel(-1, jump, 0);
    }
}

void mixer::playPoint() {
    if (isPlay) {
        Mix_PlayChannel(-1, point, 0);
    }
}

void mixer::stopbgMusic() {
    if (Mix_PlayingMusic() != 0) {
        Mix_HaltMusic();
    }
}

void mixer::playClick() {
    if (isPlay) {
        Mix_PlayChannel(-1, click, 0);
    }
}

void mixer::renderSound() {
    bool soundStateChanged = checkSound();

    if (isPlay) {
        Load(sound_img_path, 1);
    } else {
        Load(sound_mute_path, 1);
    }

    Render(posX, posY, 0);

    if (soundStateChanged) {
        if (isPlay) {
            playbgMusic();
        } else {
            stopbgMusic();
            Mix_HaltChannel(-1);
        }
    }
}

bool mixer::checkSound() {
    int x, y;
    Uint32 mouseState = SDL_GetMouseState(&x, &y);

    if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT) &&
        x > posX && x < posX + getWidth() &&
        y > posY && y < posY + getHeight()) {
        if (!isPressed) {
            isPressed = true;
            isPlay = !isPlay;
            return true;
        }
    } else {
        isPressed = false;
    }

    return false;
}

void mixer::toggleSound() {
    isPlay = !isPlay;
    if (isPlay) {
        playbgMusic();
    }
    else {
        stopbgMusic();
        Mix_HaltChannel(-1);
        SDL_PauseAudio(1);
    }
}
