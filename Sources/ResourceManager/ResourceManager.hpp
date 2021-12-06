#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <SDL.h>

#include <string>
#include <unordered_map>

class ResourceManager
{
private:
    static std::unordered_map< std::string, SDL_Texture * > map_path_to_bitmap;

public:
    ~ResourceManager();

    // Will return nullptr if will fail to load
    static SDL_Texture *load_bitmap( const char* path );
    static void unload_bitmap( const char *path );
};

#endif // __RESOURCEMANAGER_H__