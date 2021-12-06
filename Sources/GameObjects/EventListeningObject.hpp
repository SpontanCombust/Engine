#ifndef __EVENTLISTENINGOBJECT_H__
#define __EVENTLISTENINGOBJECT_H__

#include "GameObject.hpp"

#include <SDL_events.h>

class EventListeningObject : virtual public GameObject
{
public:
    virtual void handle_event( const SDL_Event& e ) = 0;
    
    virtual ~EventListeningObject() = default;
};

#endif // __EVENTLISTENINGOBJECT_H__