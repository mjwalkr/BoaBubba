//
// Created by Michael Walker on 12/31/2016.
//

#ifndef BOABUBBA_PLAYERCONTROLLER_H
#define BOABUBBA_PLAYERCONTROLLER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Player.h"
#include "SegmentController.h"

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
    // using CachedKeyboard = ActorProps::Direction; todo use 'using' instead of creating a separate enum

    PlayerController();

    ~PlayerController();

    Player* getPlayer() const;

    void preUpdate();
    void update();
    void postUpdate();

    void render(sf::RenderWindow& window);

    void moveCached();

    void setSegmentController(SegmentController* controller);

  private:
    void init();

    SegmentController* segmentController;

    std::unique_ptr<Player> m_player;
    CachedKeyboard m_cached;



    bool m_collided;
  };
}

#endif //BOABUBBA_PLAYERCONTROLLER_H
