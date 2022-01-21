#ifndef __SIMPLEEVENTLISTENINGOBJECT_H__
#define __SIMPLEEVENTLISTENINGOBJECT_H__

#include "EventListeningObject.hpp"

#include <functional>


/**
 * @brief Klasa implementująca interfejs EventListeningObject.
 * 
 */
class SimpleEventListeningObject : virtual public EventListeningObject
{
protected:
    std::function< void( const SDL_Event& ) > lambda_handler;

public:
/**
 * @brief Stwórz nowy obiekt wykorzystujący funktor.
 * 
 * @param lambda Funktor
 */
    SimpleEventListeningObject( std::function< void( const SDL_Event& ) > lambda );

/**
 * @brief Obsłuż zdarzenie.
 * 
 * @param e Zdarzenie.
 */
    void handle_event( const SDL_Event& e ) override;
};

#endif // __SIMPLEEVENTLISTENINGOBJECT_H__