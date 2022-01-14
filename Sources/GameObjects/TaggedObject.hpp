#pragma once

#include "GameObject.hpp"

#include <string>
#include <vector>

class TaggedObject : virtual public GameObject
{
private:
    std::vector< std::string > tags;

public:
    void add_tag( const char *tag );
    bool has_tag( const char *tag ) const;
};