#include "ResourceManager.hpp"

#include "Engine/Engine.hpp"

#include <SDL_image.h>


std::unordered_map< std::string, SDL_Texture * > ResourceManager::map_path_to_bitmap;
std::unordered_map< std::string, Mix_Chunk * > ResourceManager::map_path_to_sfx;
std::unordered_map< std::string, Mix_Music * > ResourceManager::map_path_to_music;
std::unordered_map< std::string, TTF_Font * > ResourceManager::map_path_to_font;

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

Mix_Chunk* ResourceManager::load_sfx( const char *path ) 
{
    auto it = map_path_to_sfx.find( path );
    if( it != map_path_to_sfx.end() )
    {
        return it->second;
    }

    Mix_Chunk *sfx = Mix_LoadWAV( path );

    if( sfx )
    {
        map_path_to_sfx[ path ] = sfx;
        return sfx;
    }

    return nullptr;
}

void ResourceManager::unload_sfx( const char *path ) 
{
    auto it = map_path_to_sfx.find( path );
    if( it != map_path_to_sfx.end() )
    {
        Mix_FreeChunk( it->second );
        map_path_to_sfx.erase( it );
    }
}

Mix_Music* ResourceManager::load_music( const char *path ) 
{
    auto it = map_path_to_music.find( path );
    if( it != map_path_to_music.end() )
    {
        return it->second;
    }

    Mix_Music *music = Mix_LoadMUS( path );

    if( music )
    {
        map_path_to_music[ path ] = music;
        return music;
    }

    return nullptr;
}

void ResourceManager::unload_music( const char *path ) 
{
    auto it = map_path_to_music.find( path );
    if( it != map_path_to_music.end() )
    {
        Mix_FreeMusic( it->second );
        map_path_to_music.erase( it );
    }
}

TTF_Font* ResourceManager::load_font( const char *path, int pt_size ) 
{
    std::string path_with_pt_size = path + std::to_string( pt_size );

    auto it = map_path_to_font.find( path_with_pt_size );
    if( it != map_path_to_font.end() )
    {
        return it->second;
    }

    TTF_Font *font = TTF_OpenFont( path, pt_size );

    if( font )
    {
        map_path_to_font[ path_with_pt_size ] = font;
        return font;
    }

    return nullptr;
}

void ResourceManager::unload_font( const char *path, int pt_size ) 
{
    std::string path_with_pt_size = path + std::to_string( pt_size );

    auto it = map_path_to_font.find( path_with_pt_size );
    if( it != map_path_to_font.end() )
    {
        TTF_CloseFont( it->second );
        map_path_to_font.erase( it );
    }
}

ResourceManager::~ResourceManager() 
{
    for( auto it = map_path_to_bitmap.begin(); it != map_path_to_bitmap.end(); ++it )
    {
        SDL_DestroyTexture( it->second );
    }
    for( auto it = map_path_to_sfx.begin(); it != map_path_to_sfx.end(); ++it )
    {
        Mix_FreeChunk( it->second );
    }
    for( auto it = map_path_to_music.begin(); it != map_path_to_music.end(); ++it )
    {
        Mix_FreeMusic( it->second );
    }
    for( auto it = map_path_to_font.begin(); it != map_path_to_font.end(); ++it )
    {
        TTF_CloseFont( it->second );
    }
}
