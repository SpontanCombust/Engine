#include "SoundEmitterObject.hpp"

void SoundEmitterObject::add_sound( const char *name, Mix_Chunk *sfx ) 
{
    map_name_to_sound[name] = Sound{ sfx, -1 };
}

void SoundEmitterObject::play_sound( const char *name, int loops ) 
{
    auto it = map_name_to_sound.find( name );
    if( it != map_name_to_sound.end() )
    {
        auto& sound = it->second;
        
        if( sound.channel != -1 )
        {
            Mix_PlayChannel( sound.channel, sound.chunk, loops );
        }
        else
        {
            sound.channel = Mix_PlayChannel( -1, sound.chunk, loops );
        }
    }
}

void SoundEmitterObject::stop_sound( const char *name ) 
{
    auto it = map_name_to_sound.find( name );
    if( it != map_name_to_sound.end() )
    {
        auto& sound = it->second;

        if( sound.channel != -1 )
        {
            Mix_HaltChannel( sound.channel );
        }
    }
}
