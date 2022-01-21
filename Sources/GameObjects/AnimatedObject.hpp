#ifndef __ANIMATEDOBJECT_H__
#define __ANIMATEDOBJECT_H__

#include "BitmapObject.hpp"
#include "UpdatableObject.hpp"
#include "Animation/Animation.hpp"

#include <unordered_map>

/**
 * @brief Klasa reprezentująca animowany obiekt.
 * 
 */
class AnimatedObject : virtual public BitmapObject, virtual public UpdatableObject
{
private:
    std::unordered_map<std::string, Animation *> map_anim_name_to_animations;
    Animation *curr_anim;

public:
    AnimatedObject();
    ~AnimatedObject() override;

/**
 * @brief Dodaje animację do obiektu.
 * 
 * @param anim Obiekt animacji.
 */
    void add_animation( const Animation& anim );
    /** @brief Rozpoczyna granie animacji. @param iterations ile razy animacja powinna być grana, -1 dla nieskonczonej ilosci razy */
    void play_animation( const char *anim_name, int iterations = -1 );

    /**
     * @brief Czy animacja się skończyła?
     * 
     * @return true Animacja skonczyla się.
     * @return false Animacjanie  skonczyla się.
     */
    bool has_animation_finished() const;

    /**
     * @brief Uzyskaj nazwę animacji.
     * 
     * @return std::string Nazwa animacji.
     */
    std::string get_animation_name() const;
    
    /**
     * @brief Czy animacja jest grana?
     * @param anim_name Nazwa animacji.
     */
    bool is_animation_playing( const char *anim_name ) const;

/**
 * @brief Aktualizuje obiekt.
 * 
 * @param dt Delta czasu.
 */
    void update(uint32_t dt) override;
};

#endif // __ANIMATEDOBJECT_H__