/**
 * Created by Michael Walker on 11/26/2016.
 *
 * Abstract class used to define all entities in the game.
 **/

#ifndef BOABUBBA_ACTOR_H
#define BOABUBBA_ACTOR_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../include/GameObject.h"

namespace boabubba
{
  class Actor : public GameObject, public sf::Drawable {
  public:
    Actor();
    virtual ~Actor() { }

    const bool isVisible() const;

    virtual void update() = 0;
    virtual void render(sf::RenderWindow &window) override;

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool m_visible;
  };
}

#endif //BOABUBBA_ACTOR_H
