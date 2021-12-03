#include "SimpleEventListeningObject.hpp"

SimpleEventListeningObject::SimpleEventListeningObject( std::function< void( const SDL_Event& ) > lambda ) 
{
    lambda_handler = lambda;
}

void SimpleEventListeningObject::handle_event(const SDL_Event& e) 
{
    lambda_handler(e);
}
