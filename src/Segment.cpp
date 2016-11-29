/**
 * Created by Michael Walker on 11/26/2016.
 **/

#include "Actor/Segment.h"

namespace boabubba
{
  Segment::Segment(const sf::Vector2i& position, Segment* follow)
    : m_follow(follow)
  {
    /**
     * Set the index of the segment. The head segment will have an index of 0,
     * while the next segment will have an index of [next segment index + 1].
     */
    if (!m_follow) { m_index = 0; }
    else { m_index = m_follow->getIndex() + 1; }

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

  Segment* Segment::getFollow() const
  {
    return m_follow;
  }

  void Segment::update()
  {

    // The head of snake's movement.
    if (!m_follow)
    {

    }
    else
    {

    }

    // Update the sprite position.
    m_sprite.setPosition(getPosition());
  }

  void Segment::updateDirection()
  {

  }
}
