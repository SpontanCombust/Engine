#include "GameObject.hpp"

#include <algorithm>

GameObject::GameObject() 
{
    is_alive = true;
}

void GameObject::add_tag( const char *tag ) 
{
    tags.insert( tag );
}

bool GameObject::has_tag( const char *tag ) const
{
    return tags.find( tag ) != tags.end();
}
