#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <string>
#include <unordered_map>

class ResourceManager
{
private:
    static std::unordered_map< std::string, SDL_Texture * > map_path_to_bitmap;
    static std::unordered_map< std::string, Mix_Chunk * > map_path_to_sfx;
    static std::unordered_map< std::string, Mix_Music * > map_path_to_music;
    static std::unordered_map< std::string, TTF_Font * > map_path_to_font;

public:
    ~ResourceManager();

    // Will return nullptr if will fail to load
    static SDL_Texture *load_bitmap( const char* path );
    static void unload_bitmap( const char *path );

    // Will return nullptr if will fail to load
    static Mix_Chunk *load_sfx( const char *path );
    static void unload_sfx( const char *path );

    // Will return nullptr if will fail to load
    static Mix_Music *load_music( const char *path );
    static void unload_music( const char *path );

    // Will return nullptr if will fail to load
    static TTF_Font *load_font( const char *path, int pt_size );
    static void unload_font( const char *path, int pt_size );
};

#endif // __RESOURCEMANAGER_H__