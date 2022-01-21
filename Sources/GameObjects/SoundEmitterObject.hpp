#pragma once

#include "GameObject.hpp"

#include <SDL_mixer.h>

#include <string>
#include <unordered_map>

    /**
     * @brief Obiekt emitujący dźwięki.
     * */
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
    /**
     * @brief Dodaje dźwięk.
     * @param name Nazwa dźwięku.
     * @param sfx Zwrócony wskaźnik na obiekt dźwięku.
     * */
    void add_sound( const char *name, Mix_Chunk *sfx );

        /**
     * @brief Uruchamia dźwięk.
     * @param name Nazwa dźwięku.
     * @param loops Ilość pętli.
     * */
    void play_sound( const char *name, int loops );

    /**
     * @brief Zatrzymuje dźwięk.
     * @param name Nazwa dźwięku.
     * */
    void stop_sound( const char *name );
};