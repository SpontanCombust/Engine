#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <string>
#include <unordered_map>

    /**
     * @brief Obsługa zasobów.
     * */
class ResourceManager
{
private:
    static std::unordered_map< std::string, SDL_Texture * > map_path_to_bitmap;
    static std::unordered_map< std::string, Mix_Chunk * > map_path_to_sfx;
    static std::unordered_map< std::string, Mix_Music * > map_path_to_music;
    static std::unordered_map< std::string, TTF_Font * > map_path_to_font;

public:
    ~ResourceManager();

    /**
     * @brief Ładuje bitmapę.
     * 
     * @param path Ścieżka do bitmapy.
     * @return SDL_Texture* 
     */
    // Will return nullptr if will fail to load
    static SDL_Texture *load_bitmap( const char* path );

        /**
     * @brief Wyładowuje bitmapę.
     * 
     * @param path Ścieżka do bitmapy.
     */
    static void unload_bitmap( const char *path );

    // Will return nullptr if will fail to load
    /**
     * @brief Ładuje dźwięk.
     * 
     * @param path Ścieżka do dźwięku.
     * @return Mix_Chunk
     */
    static Mix_Chunk *load_sfx( const char *path );

    /**
     * @brief Wyładowuje dźwięk.
     * 
     * @param path Ścieżka do dźwięku.
     */
    static void unload_sfx( const char *path );

    // Will return nullptr if will fail to load
    // Will return nullptr if will fail to load
    /**
     * @brief Ładuje muzykę.
     * 
     * @param path Ścieżka do muzyki.
     * @return Mix_Music
     */
    static Mix_Music *load_music( const char *path );

    /**
     * @brief Wyładowuje muzykę.
     * 
     * @param path Ścieżka do muzyki.
     */
    static void unload_music( const char *path );

    // Will return nullptr if will fail to load

    /**
     * @brief Ładuje font.
     * 
     * @param path Ścieżka do fontu.
     * @return TTF_Font
     */
    static TTF_Font *load_font( const char *path, int pt_size );

        /**
     * @brief Wyładowuje font.
     * 
     * @param path Ścieżka do fontu.
     */
    static void unload_font( const char *path, int pt_size );
};

#endif // __RESOURCEMANAGER_H__