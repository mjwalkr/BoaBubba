/**
 * Created by Michael Walker on 11/26/2016.
 **/

#include "Actor/Actor.h"

namespace boabubba
{
  Actor::Actor()
  {
    // TODO: This is temorary code for displaying a placeholder sprite
  }

  void Actor::setPosition(const sf::Vector2i& position)
  {
    m_position.x = static_cast<float>(position.x);
    m_position.y = static_cast<float>(position.y);
  }

  void Actor::setPosition(const sf::Vector2f& position)
  {
    m_position = position;
  }

  const sf::Vector2f& Actor::getPosition() const
  {
    return m_position;
  }

  void Actor::setPositionPrevious(const sf::Vector2i& position)
  {
    m_positionPrevious.x = static_cast<float>(position.x);
    m_positionPrevious.y = static_cast<float>(position.y);
  }

  void Actor::setPositionPrevious(const sf::Vector2f& position)
  {
    m_positionPrevious = position;
  }

  const sf::Vector2f& Actor::getPositionPrevious() const
  {
    return m_positionPrevious;
  }

  void Actor::setPosInt(const sf::Vector2i& position)
  {
    m_posInt = position;
  }

  const sf::Vector2i& Actor::getPosInt() const
  {
    return m_posInt;
  }

  void Actor::setGrid(const sf::Vector2i& grid)
  {
    m_grid = grid;
  }

  const sf::Vector2i& Actor::getGrid() const
  {
    return m_grid;
  }

  void Actor::setGridPrevious(const sf::Vector2i& grid)
  {
    m_gridPrevious = grid;
  }

  const sf::Vector2i& Actor::getGridPrevious() const
  {
    return m_gridPrevious;
  }

  const sf::Vector2i Actor::getGridPosition(const sf::Vector2i& grid) const
  {
    return sf::Vector2i(m_grid.x * GameProps::PROP_GRID_WIDTH, m_grid.y * GameProps::PROP_GRID_HEIGHT);
  }

  void Actor::setDirection(const Direction& direction)
  {
    m_direction = direction;
  }

  const Direction& Actor::getDirection() const
  {
    return m_direction;
  }

  void Actor::setSpeed(const sf::Vector2f& speed)
  {
    m_speed = speed;
  }

  const sf::Vector2f& Actor::getSpeed() const
  {
    return m_speed;
  }

  const bool Actor::isVisible() const
  {
    return m_visible;
  }

  const bool Actor::isSnapped() const
  {
    sf::Vector2i pos = getGridPosition(m_grid);
    return (m_posInt.x == pos.x) && (m_posInt.y == pos.y);
  }

  void Actor::render(sf::RenderWindow& window)
  {
    window.draw(*this);
  }

  void Actor::draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    if (isVisible())
      target.draw(m_sprite, states);
  }
}
