#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <string>
#include <unordered_set>

/**
 * @brief Podstawowa klasa obiektów gry.
 * 
 */
class GameObject
{
private:
    std::unordered_set< std::string > tags;

public:
/**
 * @brief Czy obiekt jest używany przez silnik?
 * 
 */
    bool is_alive;

    GameObject();
    virtual ~GameObject() = default; // interface needs at least virtual destructor

/**
 * @brief Dodaj tag.
 * @param tag Oznaczenie w formie tagu.
 */
    void add_tag( const char *tag );
/**
 * @brief Czy ma zadany tag?
 * @param tag Oznaczenie w formie tagu.
 */
    bool has_tag( const char *tag ) const;
};

#endif // __GAMEOBJECT_H__