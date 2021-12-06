#ifndef __SIMPLEEVENTLISTENINGOBJECT_H__
#define __SIMPLEEVENTLISTENINGOBJECT_H__

#include "EventListeningObject.hpp"

#include <functional>


class SimpleEventListeningObject : virtual public EventListeningObject
{
protected:
    std::function< void( const SDL_Event& ) > lambda_handler;

public:
    SimpleEventListeningObject( std::function< void( const SDL_Event& ) > lambda );

    void handle_event( const SDL_Event& e ) override;
};

#endif // __SIMPLEEVENTLISTENINGOBJECT_H__