/**
 * Created by Michael Walker on 11/26/2016.
 **/

#include "../include/Actor.h"

namespace boabubba
{
  Actor::Actor()
  {

  }

  const bool Actor::isVisible() const
  {
    return m_visible;
  }

  void Actor::render(sf::RenderWindow& window)
  {
    window.draw(*this);
  }

  void Actor::draw(sf::RenderTarget& target, sf::RenderStates states) const
  {

  }
}
