/**
 * Created by Michael Walker on 11/26/2016.
 **/

#include "Actor/Actor.h"

namespace boabubba
{
  Actor::Actor()
  {
    // TODO: This is temporary code for displaying a placeholder sprite
  }

  void Actor::setPosition(const Grid& position)
  {
    m_position.x = static_cast<float>(position.x * GameProps::PROP_GRID_WIDTH);
    m_position.y = static_cast<float>(position.y * GameProps::PROP_GRID_HEIGHT);

    m_posInt.x = position.x * GameProps::PROP_GRID_WIDTH;
    m_posInt.y = position.y * GameProps::PROP_GRID_HEIGHT;

    m_grid = position;
    m_gridCurrent = position;
    m_gridPrevious = position;
  }

  void Actor::setPosition(const sf::Vector2f& position)
  {
    m_position = position;
  }

  const sf::Vector2f& Actor::getPosition() const
  {
    return m_position;
  }

  void Actor::setPositionPrevious(const Grid& position)
  {
    m_positionPrevious.x = static_cast<float>(position.x * GameProps::PROP_GRID_WIDTH);
    m_positionPrevious.y = static_cast<float>(position.y * GameProps::PROP_GRID_HEIGHT);
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

  void Actor::setGrid(const Grid& grid)
  {
    m_grid = grid;
  }

  const Grid& Actor::getGrid() const
  {
    return m_grid;
  }

  void Actor::setGridCurrent(const Grid &grid){
    m_gridCurrent = grid;
  }

  const Grid& Actor::getGridCurrent() const
  {
    return m_gridCurrent;
  }

  void Actor::setGridPrevious(const Grid &grid){
    m_gridPrevious = grid;
  }

  const Grid& Actor::getGridPrevious() const
  {
    return m_gridPrevious;
  }

  const Grid Actor::getGridPosition(const Grid& grid) const
  {
    return Grid(grid.x * GameProps::PROP_GRID_WIDTH, grid.y * GameProps::PROP_GRID_HEIGHT);
  }

  void Actor::updateGrid(const ActorProps::Direction direction)
  {
    // Update the previous grid position.
    m_gridPrevious = m_gridCurrent;

    // Update the current grid position
    m_gridCurrent = m_grid;

    // Move the grid (x,y) position.
    m_grid.move(direction);
  }

  void Actor::setDirection(const ActorProps::Direction& direction)
  {
    m_direction = direction;
  }

  const ActorProps::Direction& Actor::getDirection() const
  {
    return m_direction;
  }

  const ActorProps::Direction Actor::directionFor(const Grid &from, const Grid &to)
  {
    if (from.equals(to))
    {
      return ActorProps::Direction::None;
    }
    else if (from.x == to.x)
    {
      if (from.y > to.y)
      {
        return ActorProps::Direction::Up;
      }
      else
      {
        return ActorProps::Direction::Down;
      }
    }
    else if (from.y == to.y)
    {
      if (from.x > to.x)
      {
        return ActorProps::Direction::Left;
      }
      else
      {
        return ActorProps::Direction::Right;
      }
    }
    return ActorProps::Direction::None;
  }

  void Actor::setLocation(const Location &location)
  {
    m_location = location;
  }

  const Location& Actor::getLocation() const
  {
    return m_location;
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

  void Actor::moveGridBased()
  {
    const sf::Vector2i myGridPos = getGridPosition(getGrid());

    // Move the actor's position.
    switch (getDirection())
    {
      case ActorProps::Direction::Left: m_position.x = std::max(m_position.x - m_speed.x, float(myGridPos.x)); break;
      case ActorProps::Direction::Right: m_position.x = std::min(m_position.x + m_speed.x, float(myGridPos.x)); break;
      case ActorProps::Direction::Up: m_position.y = std::max(m_position.y - m_speed.y, float(myGridPos.y)); break;
      case ActorProps::Direction::Down: m_position.y = std::min(m_position.y + m_speed.y, float(myGridPos.y)); break;
      default: break;
    }

    // Snap the position when the actor has traversed to the grid position.
    if (((m_position.x <= float(myGridPos.x)) && (getDirection() == ActorProps::Direction::Left)) ||
        ((m_position.x >= float(myGridPos.x)) && (getDirection() == ActorProps::Direction::Right)) ||
        ((m_position.y <= float(myGridPos.y)) && (getDirection() == ActorProps::Direction::Up)) ||
        ((m_position.y >= float(myGridPos.y)) && (getDirection() == ActorProps::Direction::Down)))
    {
      setPosition(sf::Vector2f(static_cast<float>(myGridPos.x), static_cast<float>(myGridPos.y)));
      setPosInt(sf::Vector2i(myGridPos.x, myGridPos.y));
    }
  }

  void Actor::move()
  {
    // do nothing here
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
