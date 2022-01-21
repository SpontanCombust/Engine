#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL.h>
#include <glm/glm.hpp>

#include <cstdint>
#include <string>

class Animation
{
private:
/**
 * @brief Nazwa animacji.
 * 
 */
    std::string name;

/**
 * @brief Klatka danej części animacji.
 * 
 */
    SDL_Texture *used_bitmap;

    /**
 * @brief Flaga oznaczająca obrócenie horyzontalne lub vertykalne.
 * 
 */
    SDL_RendererFlip flip_modifier;

    
/**
 * @brief Flaga oznaczająca obrócenie horyzontalne lub vertykalne.
 * 
 */
    SDL_Rect frame_start_rect;
    uint32_t frame_count;
    uint32_t anim_duration;

    uint32_t anim_timer;
    int iterations_left;
    SDL_Rect curr_clipping_rect;


public:
    /**
     * @brief Konstruktor animacji.
     * 
     * @param bitmap Bitmapa używana dla animacji; właściwie nie jest używana przez tę klasę, jedynie jest przechowywana 
     * @param start_point Punkt spośród pikseli, gdzie ma się zaczynać animacja
     * @param frame_size Rozmiar w pikselach każdej klatki w animacji
     * @param frame_count Ile indywidualnych klatek jest w animacji
     * @param anim_duration Ile powinna trwać animacja w milisekundach
     */
    Animation( const char *name, SDL_Texture *bitmap, SDL_RendererFlip flip_modifier, glm::ivec2 start_point, glm::ivec2 frame_size, uint32_t frame_count, uint32_t anim_duration );

       /**
     * @brief Ustaw czas trwania animacji w milisekundach.
     * @param anim_duration Czas trwania w milisekundach.
     * */
    void set_anim_duration( uint32_t anim_duration );

        /**
     * @brief Uzyskuje używaną bitmapę dla animacji.
     * */
    SDL_Texture *get_used_bitmap() const;

    /**
     * @brief Uzyskuje używany modyfikator przekształcenia dla animacji.
     * */
    SDL_RendererFlip get_flip_modifier() const;

        /**
     * @brief Uzyskuje nazwę animacji.
     * */
    const std::string& get_name() const;


    /**
     * @brief Pozyskuje prostokąt ograniczający widzianą animację.
     * */
    SDL_Rect get_curr_clipping_rect() const;

    /** @brief Ile razy animacja powinna być odgrywana.
     * @param num_of_iterations Ile razy animacja powinna być odgrywana, -1 dla nieskończonej ilości razy.
    */
    void reset( int num_of_iterations = -1 );

    /** @brief Ile razy animacja powinna być odgrywana.
     * @param delta_time Różnica czasu.
    */
    void advance( uint32_t delta_time );

        /** @brief Czy animacja się skończyła?
*/
    bool has_finished() const;
};

#endif // __ANIMATION_H__