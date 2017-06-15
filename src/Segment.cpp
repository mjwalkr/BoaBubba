/**
 * Created by Michael Walker on 11/26/2016.
 **/

#include "Actor/Segment.h"

namespace boabubba
{
  Segment::Segment(const Grid& grid, Segment* follow)
    : m_follow(follow)
    , m_front(false)
    , m_collided(false)
    , m_waitOnHead(false)
  {
    setIndex(); // automatically set the index

    setPosition(grid);
    //setSpeed(sf::Vector2f(1.02f, 1.02f));
    setSpeed(sf::Vector2f(1.5f, 1.5f));
    setDirection(ActorProps::Direction::None);
    setLocation(Location(grid.x * GameProps::PROP_GRID_WIDTH,
                         grid.y * GameProps::PROP_GRID_HEIGHT));

    float x = static_cast<float>(grid.x);
    float y = static_cast<float>(grid.y);

    m_sprite = sf::CircleShape();
    if (m_index == 0)
      m_sprite.setFillColor(sf::Color::Blue);
    else
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

  const Grid& Segment::getMarker()
  {
    return m_marker;
  }

  void Segment::setMarker(const Grid& marker)
  {
    m_marker = marker;
  }

  void Segment::setFront(const bool front)
  {
    m_front = front;
  }

  void Segment::setCollided(const bool collided)
  {
    m_collided = collided;
  }

  void Segment::setWaitOnHead(const bool wait){
    m_waitOnHead = wait;
  }

  void Segment::setDist(const float dist)
  {
    m_dist = dist;
  }

  const bool Segment::isFront()
  {
    return m_front;
  }

  const bool Segment::isCollided() const
  {
    return m_collided;
  }

  const bool Segment::isWaitOnHead() const
  {
    return m_waitOnHead;
  }

  void Segment::preUpdate()
  {}

  void Segment::update()
  {
    // Update the segment's direction (note: the head segment will not be updated from this method)
    updateDirection();

    // Set the segment as the front.
    m_front = ((!m_follow && !m_collided && ((getPosInt().x != getGridPosition(getGrid()).x) || (getPosInt().y != getGridPosition(getGrid()).y))) || (m_follow && m_follow->getDist() == 0 && getDirection() != ActorProps::Direction::None));

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

  void Segment::postUpdate()
  {}

  void Segment::segmentMoveAsLeader()
  {
    move();

    if (getDirection() == ActorProps::Direction::Left || getDirection() == ActorProps::Direction::Right)
    {
      setDist(std::abs(getPosition().x - getGridPosition(getGridCurrent()).x));
    }
    else if (getDirection() == ActorProps::Direction::Up || getDirection() == ActorProps::Direction::Down)
    {
      setDist(std::abs(getPosition().y - getGridPosition(getGridCurrent()).y));
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
    if (((getPosInt().x != getGridPosition(getGrid()).x) || (getPosInt().y != getGridPosition(getGrid()).y)) && !m_follow->isWaitOnHead())
    {
      const sf::Vector2i myGridCurrPos = getGridPosition(getGridCurrent());
      const float dist = m_follow->getDist();

      switch(getDirection())
      {
        case ActorProps::Direction::Left: setPosition(sf::Vector2f(myGridCurrPos.x - dist, getPosition().y)); break;
        case ActorProps::Direction::Right: setPosition(sf::Vector2f(myGridCurrPos.x + dist, getPosition().y)); break;
        case ActorProps::Direction::Up: setPosition(sf::Vector2f(getPosition().x, myGridCurrPos.y - dist)); break;
        case ActorProps::Direction::Down: setPosition(sf::Vector2f(getPosition().x, myGridCurrPos.y + dist)); break;
        default: break;
      }
      // Do not snap the segments here, snap them when the front segment is snapped.
      // The direction is set, and the segment is moving a set distance.
      if (getDirection() != ActorProps::Direction::None && abs(dist) > 0.f)
      {
        setSnapped(false);
      }
    }
    setWaitOnHead(m_follow->isWaitOnHead());
    setDist(m_follow->getDist());
  }

  void Segment::updateDirection()
  {
    // The 'head' segment should not invoke this method.
    if (!getFollow()) return;

    // todo could use another variable to restrict updating the direction when not needed
    if (getDirection() == ActorProps::Direction::None)
    {
      ActorProps::Direction dir = ActorProps::Direction::None;
      if (getGrid().x > m_follow->getMarker().x)
      {
        dir = ActorProps::Direction::Left;
      }
      else if (getGrid().x < m_follow->getMarker().x)
      {
        dir = ActorProps::Direction::Right;
      }
      else if (getGrid().y > m_follow->getMarker().y)
      {
        dir = ActorProps::Direction::Up;
      }
      else if (getGrid().y < m_follow->getMarker().y)
      {
        dir = ActorProps::Direction::Down;
      }

      setDirection(dir);
      updateGrid(dir);
    }
  }
}
