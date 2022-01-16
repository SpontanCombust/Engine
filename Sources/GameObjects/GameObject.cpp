#include "GameObject.hpp"

#include <algorithm>

GameObject::GameObject() 
{
    is_alive = true;
}

void GameObject::add_tag( const char *tag ) 
{
    tags.push_back( tag );
}

bool GameObject::has_tag( const char *tag ) const
{
    std::string str_tag = std::string( tag );

    return std::any_of( 
        tags.begin(), 
        tags.end(), 
        [&str_tag]( const std::string& t ) 
        { 
            return t == str_tag; 
        }
    );
}
