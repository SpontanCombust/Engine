#pragma once

#include "GameObject.hpp"

#include <SDL_mixer.h>

#include <string>
#include <unordered_map>

class SoundEmitterObject : virtual public GameObject
{
private:
    struct Sound
    {
        Mix_Chunk *chunk = nullptr;
        int channel = -1;
    };

    std::unordered_map<std::string, Sound> map_name_to_sound;


public:
    void add_sound( const char *name, Mix_Chunk *sfx );
    void play_sound( const char *name, int loops );
    void stop_sound( const char *name );
};