#ifndef __BITMAPOBJECT_H__
#define __BITMAPOBJECT_H__

#include "ModelObject.hpp"
#include "DrawableObject.hpp"

#include <SDL.h>

/**
 * @brief Obiekt reprezentujacy bitmape.
 * 
 */
class BitmapObject : virtual public ModelObject, virtual public DrawableObject
{
public:
/**
 * @brief Rozmiar tekstury
 * 
 */
    glm::ivec2 tex_size;

    /**
 * @brief Bitmapa dla SDL.
 * 
 */
    SDL_Texture *bitmap;

        /**
 * @brief Zabarwienie bitmapy.
 * 
 */
    glm::i8vec3 bitmap_tint;

        /**
 * @brief Prostokat przycinajacy.
 * 
 */
    SDL_Rect clip_rect;

        /**
 * @brief Zmiany w obrocie bitmapy.
 * 
 */
    SDL_RendererFlip flip;
    
    BitmapObject();
/**
 * @brief Tworzy bitmape z obiektu SDL_Texture.
 * @param bitmap Tekstura SDL.
 */
    BitmapObject( SDL_Texture *bitmap );

    /**
 * @brief Tworzy bitmape z pliku na dysku.
 * @param bitmap_file_path Ściezka do bitmapy na dysku.
 */
    BitmapObject( const char *bitmap_file_path );

    ~BitmapObject();

/**
 * @brief Ustawia teksture.
 * 
 * @param bitmap Ustawiana tekstura
 */
    void set_bitmap( SDL_Texture *bitmap );

/**
 * @brief Ustawia docelowy rozmiar.
 * 
 * @param size Rozmiar.
 */
    void set_target_size( glm::vec2 size ) override;

    /**
 * @brief Ustawia docelowy rozmiar z opcjonalnym zachowaniem aspektu.
 * 
 * @param size Rozmiar.
 * @param keep_aspect_ratio Czy proporcje mają być zachowane?
 */
    virtual void set_target_size( glm::vec2 size, bool keep_aspect_ratio );

        /**
 * @brief Uzyskuje docelowy rozmiar.
 * 
 * @return Zwrócony docelowy rozmiar.
 */
    glm::vec2 get_target_size() const override;


        /**
 * @brief Rysuje bitmapę.
 */
    void draw() override;
};

#endif // __BITMAPOBJECT_H__