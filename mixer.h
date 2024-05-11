#ifndef MIXER_H_
#define MIXER_H_

#include "CommonFunc.h"

using namespace std;

class mixer:LoadTexture {
public:
    bool init();
    void Destroy();

    void playJump();
    void muteJump();

    void playHit();
    void muteHit();

    void playPoint();
    void mutePoint();

    void playClick();
    void muteClick();

    void playbgMusic();
    void stopbgMusic();

    void renderSound();

    bool checkSound();

    void toggleSound();
    bool isMute = false;

private:
    const int posX = 107;
    const int posY = 267;

    bool isPlay = false;
    bool isPressed = false;

    Mix_Music* bgMusic = nullptr;
    Mix_Chunk* jump = nullptr;
    Mix_Chunk* hit = nullptr;
    Mix_Chunk* click = nullptr;
    Mix_Chunk* point = nullptr;

    string bgMusic_path = "resource/mixer/bgMusic.mp3";

    string jump_path = "resource/mixer/jump.wav";
    string hit_path = "resource/mixer/hit.wav";
    string point_path = "resource/mixer/point.wav";
    string click_button = "resource/mixer/clickbutton.wav";

    string sound_img_path = "resource/image/sound.png";
    string sound_mute_path = "resource/image/sound-mute.png";

};

#endif // MIXER_H_
