//
// Created by Michael Walker on 12/31/2016.
//

#include "Actor/Player.h"

namespace boabubba
{
  Player::Player(const Grid& startPosition)
  {
    setPosition(startPosition);
    setSpeed(sf::Vector2f(1.f, 0.9f));
    setDirection(ActorProps::Direction::None);
    setLocation(Location(startPosition.x * GameProps::PROP_GRID_WIDTH,
                         startPosition.y * GameProps::PROP_GRID_HEIGHT));

    float x = static_cast<float>(getPosition().x);
    float y = static_cast<float>(getPosition().y);

    m_sprite = sf::CircleShape();
    m_sprite.setFillColor(sf::Color::Red);
    m_sprite.setRadius(GameProps::PROP_GRID_WIDTH / 2);
    m_sprite.setPosition(sf::Vector2f(x, y));
  }

  void Player::preUpdate()
  {}

  void Player::update()
  {
    moveGridBased();
    m_sprite.setPosition(getPosition().x, getPosition().y);
  }

  void Player::postUpdate()
  {}
}