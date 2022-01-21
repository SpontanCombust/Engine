#ifndef __EVENTLISTENINGOBJECT_H__
#define __EVENTLISTENINGOBJECT_H__

#include "GameObject.hpp"

#include <SDL_events.h>

/**
 * @brief Interfejs dający funkcje do nasłuchiwania na zdarzenia.
 * 
 */
class EventListeningObject : virtual public GameObject
{
public:
/**
 * @brief Obsłuż zdarzenie.
 * @param e Zdarzenie
 * 
 */
    virtual void handle_event( const SDL_Event& e ) = 0;
    
    virtual ~EventListeningObject() = default;
};

#endif // __EVENTLISTENINGOBJECT_H__