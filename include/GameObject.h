/**
 * Created by Michael Walker on 11/26/2016.
 *
 * Defines every object in the game.
 **/

#ifndef BOABUBBA_GAMEOBJECT_H
#define BOABUBBA_GAMEOBJECT_H

#include <SFML/Graphics/RenderWindow.hpp>

namespace boabubba
{
  class GameObject
  {
  public:
    GameObject() { }
    virtual ~GameObject() { }
    virtual void preUpdate() = 0;
    virtual void update() = 0;
    virtual void postUpdate() = 0;
    virtual void render(sf::RenderWindow& window) = 0;
  };
}


#endif //BOABUBBA_GAMEOBJECT_H
