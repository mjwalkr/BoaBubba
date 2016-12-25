/**
 * Created by Michael Walker on 11/26/2016.
 **/

#include "Actor/Segment.h"

namespace boabubba
{
  Segment::Segment(const sf::Vector2i& position, Segment* follow)
    : m_follow(follow)
    , m_front(false)
  {
    setIndex(); // automatically set the index

    setPosition(position);
    setSpeed(sf::Vector2f(0.3f, 0.3f));
    setDirection(boabubba::Direction::None);

    float x = static_cast<float>(position.x);
    float y = static_cast<float>(position.y);

    m_sprite = sf::CircleShape();
    m_sprite.setFillColor(sf::Color::Green);
    m_sprite.setRadius(GameProps::PROP_GRID_WIDTH / 2);
    m_sprite.setPosition(sf::Vector2f(x, y));
  }

  const int Segment::getIndex() const
  {
    return m_index;
  }

  // private
  void Segment::setIndex()
  {
    if (!m_follow) { m_index = 0; }
    else { m_index = m_follow->getIndex() + 1; }
  }

  Segment* Segment::getFollow() const
  {
    return m_follow;
  }

  const float Segment::getDist() const
  {
    return m_dist;
  }

  const sf::Vector2i& Segment::getMarker()
  {
    return m_marker;
  }

  void Segment::setMarker(const sf::Vector2i& marker)
  {
    m_marker = marker;
  }

  void Segment::setFront(const bool front)
  {
    m_front = front;
  }

  void Segment::setDist(const float dist)
  {
    m_dist = dist;
  }

  const bool Segment::isFront()
  {
    return m_front;
  }

  void Segment::update()
  {
    // Update the segment's direction (note: the head segment will not be updated from this method)
    updateDirection();

    // Set the segment as the front.
    // When 'this' segment is the head, and it is moving towards the grid position, or
    // the segment 'this' is following isn't moving (could replace with checking if Direction = None?)
    m_front = ((!m_follow && !isSnapped()) || (m_follow && m_follow->getDist() == 0 && getDirection() != boabubba::Direction::None));

    // The head of snake's movement.
    if (isFront())
    {
      segmentMoveAsLeader();
    }
    else
    {
      segmentMoveAsFollower();
    }

    // Update the sprite position.
    m_sprite.setPosition(getPosition());
  }

  void Segment::segmentMoveAsLeader()
  {
    moveGridBased();

    if (getDirection() == boabubba::Direction::Left || getDirection() == boabubba::Direction::Right)
    {
      setDist(std::abs(getPosition().x - getGridPosition(getGridPrevious()).x));
    }
    else if (getDirection() == boabubba::Direction::Up || getDirection() == boabubba::Direction::Down)
    {
      setDist(std::abs(getPosition().y - getGridPosition(getGridPrevious()).y));
    }
    else
    {
      setDist(0.0f);
    }
  }

  void Segment::segmentMoveAsFollower()
  {
    if (!m_follow) return;

    // When the segment has a direction to move in..
    if (!isSnapped())
    {
      const sf::Vector2i myGridPrevPos = getGridPosition(getGridPrevious());
      const float dist = m_follow->getDist();

      switch(getDirection())
      {
        case boabubba::Direction::Left: setPosition(sf::Vector2f(myGridPrevPos.x - dist, getPosition().y)); break;
        case boabubba::Direction::Right: setPosition(sf::Vector2f(myGridPrevPos.x + dist, getPosition().y)); break;
        case boabubba::Direction::Up: setPosition(sf::Vector2f(getPosition().x, myGridPrevPos.y - dist)); break;
        case boabubba::Direction::Down: setPosition(sf::Vector2f(getPosition().x, myGridPrevPos.y + dist)); break;
      }
      // Do not snap the segments here, snap them when the front segment is snapped.
    }
    setDist(m_follow->getDist());
  }

  void Segment::updateDirection()
  {
    // The 'head' segment should not invoke this method.
    if (!getFollow()) return;

    // todo could use another variable to restrict updating the direction when not needed
    if (getDirection() == boabubba::Direction::None)
    {
      boabubba::Direction dir = boabubba::Direction::None;
      if (getGrid().x > m_follow->getMarker().x)
      {
        dir = boabubba::Direction::Left;
      }
      else if (getGrid().x < m_follow->getMarker().x)
      {
        dir = boabubba::Direction::Right;
      }
      else if (getGrid().y > m_follow->getMarker().y)
      {
        dir = boabubba::Direction::Up;
      }
      else if (getGrid().y < m_follow->getMarker().y)
      {
        dir = boabubba::Direction::Down;
      }

      setDirection(dir);
      updateGrid(dir);
    }
  }
}
