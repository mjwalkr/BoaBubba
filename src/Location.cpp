/**
 * Created by Michael Walker on 11/26/2016.
 **/

#include "Location.h"

namespace boabubba
{
  Location::Location()
  {

  }

  Location::Location(const int x, const int y)
  {
    m_position = sf::Vector2i(x, y);
  }

  Location::Location(const sf::Vector2i &position)
  {
    m_position = position;
  }

  bool Location::operator==(const Location other)
  {
    return (m_position.x == other.m_position.x && m_position.y == other.m_position.y);
  }

  bool Location::operator!=(const Location other)
  {
    return (m_position.x != other.m_position.x || m_position.y != other.m_position.y);
  }

  const sf::Vector2i& Location::getPosition() const
  {
    return m_position;
  }

  int Location::getCoords(const Location& location)
  {
    const sf::Vector2i position = location.getPosition();
    return getCoords(position.x, position.y);
  }

  int Location::getCoords(const int x, const int y)
  {
    return (x * GameProps::PROP_SCREEN_WIDTH) + y;
  }
}