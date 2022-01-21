#pragma once

#include "ModelObject.hpp"

#include <glm/glm.hpp>

/**
 * @brief Zestaw flag określających działanie kolizji.
 * 
 */
enum CollisionPolicy
{
    /**
    * @brief Nie nie rob z kolizja.
    * */
    COLLISION_POLICY_NONE        = 0,
    /**
    * @brief Kolizja dziala na obiekt.
    * */
    COLLISION_POLICY_AFFECTED    = 1,
        /**
    * @brief Obiekt jest oddziałujący.
    * */
    COLLISION_POLICY_AFFECTING   = 2
};

/**
 * @brief Obiekty obsługujące kolizje.
 * 
 */
class CollidableObject : virtual public ModelObject
{
public:

/**
 * @brief Rodzaj działania dla kolizji.
 * 
 */
    int collision_policy; // a logic sum of CollisionPolicy flags

    /**
 * @brief Przesunięcie bryły kolizji.
 * 
 */
    glm::vec2 collider_offset;
    
        /**
 * @brief Rozmiar bryły kolizji.
 * 
 */
    glm::vec2 collider_size;

    CollidableObject();

            /**
 * @brief Zwraca true jesli kolizja się wydarza.
 * @param other_obj Drugi obiekt z którym kolidujemy.
 */
    virtual bool resolve_collision( CollidableObject& other_obj );

/**
 * @brief Ustaw docelowy rozmiar.
 * @param size  docelowy rozmiar.
 * 
 */
    void set_target_size( glm::vec2 size ) override;

    /**
 * @brief Uzyskaj docelowy rozmiar.
 * 
 */
    glm::vec2 get_target_size() const override;
};
