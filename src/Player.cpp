//
// Created by Michael Walker on 12/31/2016.
//

#include "Actor/Player.h"

namespace boabubba
{
  Player::Player(const Grid& startPosition)
  {
    setPosition(startPosition);
    setSpeed(sf::Vector2f(1.3f, 1.3f));
    setDirection(ActorProps::Direction::None);
    setLocation(Location(startPosition.x * GameProps::PROP_GRID_WIDTH,
                         startPosition.y * GameProps::PROP_GRID_HEIGHT));

    float x = getPosition().x;
    float y = getPosition().y;

    m_sprite = sf::CircleShape();
    m_sprite.setFillColor(sf::Color::Red);
    m_sprite.setRadius(GameProps::PROP_GRID_WIDTH / 2);
    m_sprite.setPosition(sf::Vector2f(x, y));

    m_ground = true; // todo to remove
  }

  void Player::preUpdate()
  {}

  void Player::update()
  {
    move();
  }

  void Player::postUpdate()
  {}

  void Player::setGround(const bool ground)
  {
    m_ground = ground;
  }

  // override
  void Player::render(sf::RenderWindow &window)
  {
    // for debugging purposes, draw the grid space
    /*
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::Cyan);
    rect.setPosition(getGridPosition(getGridCurrent()).x, getGridPosition(getGridCurrent()).y);
    rect.setSize(sf::Vector2f(GameProps::PROP_GRID_WIDTH, GameProps::PROP_GRID_HEIGHT));
    window.draw(rect);
    */
    m_sprite.setFillColor((m_ground) ? sf::Color::Red : sf::Color::Yellow);
    m_sprite.setPosition(getPosition().x, getPosition().y);

    Actor::render(window);
  }
}