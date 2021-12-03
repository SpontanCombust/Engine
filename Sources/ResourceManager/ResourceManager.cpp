#include "ResourceManager.hpp"

#include "Engine/Engine.hpp"

#include <SDL_image.h>


std::unordered_map< std::string, SDL_Texture * > ResourceManager::map_path_to_bitmap;

SDL_Texture* ResourceManager::load_bitmap(const char* path) 
{
    auto it = map_path_to_bitmap.find( path );
    if( it != map_path_to_bitmap.end() )
    {
        return it->second;
    }

    SDL_Surface *surf = IMG_Load( path );

    if( surf )
    {
        SDL_Texture *tex = SDL_CreateTextureFromSurface( Engine::get_instance()->sdl_renderer, surf );
        SDL_FreeSurface( surf );
        map_path_to_bitmap[ path ] = tex;
        return tex;
    }

    return nullptr;
}

void ResourceManager::unload_bitmap(const char *path) 
{
    auto it = map_path_to_bitmap.find( path );
    if( it != map_path_to_bitmap.end() )
    {
        SDL_DestroyTexture( it->second );
        map_path_to_bitmap.erase( it );
    }
}

ResourceManager::~ResourceManager() 
{
    for( auto it = map_path_to_bitmap.begin(); it != map_path_to_bitmap.end(); ++it )
    {
        SDL_DestroyTexture( it->second );
    }
}
