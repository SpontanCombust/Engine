#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <string>
#include <unordered_set>

class GameObject
{
private:
    std::unordered_set< std::string > tags;

public:
    bool is_alive;

    GameObject();
    virtual ~GameObject() = default; // interface needs at least virtual destructor

    void add_tag( const char *tag );
    bool has_tag( const char *tag ) const;
};

#endif // __GAMEOBJECT_H__