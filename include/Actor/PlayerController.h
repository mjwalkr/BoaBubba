//
// Created by Michael Walker on 12/31/2016.
//

#ifndef BOABUBBA_PLAYERCONTROLLER_H
#define BOABUBBA_PLAYERCONTROLLER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Player.h"

namespace boabubba
{
  class PlayerController
  {
  public:
    enum class CachedKeyboard
    {
      Left = sf::Keyboard::Left,
      Right = sf::Keyboard::Right,
      Up = sf::Keyboard::Up,
      Down = sf::Keyboard::Down,
      Unknown = sf::Keyboard::Unknown
    };

    PlayerController();

    const Grid& getPlayerGrid() const;
    const Grid& getPlayerGridPrevious() const;
    const sf::Vector2f& getPlayerPosition() const;

    void preUpdate();
    void update();
    void postUpdate();

    void render(sf::RenderWindow& window);

    // these are two types of movement, one of which the Player will have in the final game.
    // moveFree - grid-less movement
    // moveCached - grid movement
    void moveFree();
    void moveCached();

  private:
    void init();

    std::unique_ptr<Player> m_player;
    CachedKeyboard m_cached;
  };
}

#endif //BOABUBBA_PLAYERCONTROLLER_H
