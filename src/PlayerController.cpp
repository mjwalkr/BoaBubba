//
// Created by Michael Walker on 12/31/2016.
//

#include "Actor/PlayerController.h"

namespace boabubba
{
  PlayerController::PlayerController()
  {
    init();
  }

  PlayerController::~PlayerController()
  {
    segmentController = nullptr;
  }

  void PlayerController::init()
  {
    m_player.reset(new Player(Grid(5, 5)));
    m_cached = CachedKeyboard::Unknown;
    m_collided = false;
  }

  Player* PlayerController::getPlayer() const
  {
    return m_player.get();
  }

  void PlayerController::preUpdate()
  {
    if (m_player)
    {
      moveCached();
    }
  }

  void PlayerController::update()
  {
    if (m_player)
    {
      m_player->update();
    }
  }

  void PlayerController::postUpdate()
  {
    // We need to verify if the player is running into a segment. For prototype, use the segment map?
    if (!m_player->isSnapped()) // todo this should probably just check if the head segment is NOT snapped
    {
      // Is the head segment approaching a grid position that is currently occupied by another segment?
      // Is the head segment approaching a grid position that will is being approached by another segment?
      const Grid grid = m_player->getGrid();

      // Testing for collision only when the head segment is nearing its destination
      float dist = GameProps::PROP_GRID_WIDTH;
      if (m_player->getDirection() == ActorProps::Direction::Left || m_player->getDirection() == ActorProps::Direction::Right) {
        dist = abs(m_player->getGridPosition(grid).x - m_player->getPosition().x);
      }
      else if (m_player->getDirection() == ActorProps::Direction::Up || m_player->getDirection() == ActorProps::Direction::Down) {
        dist = abs(m_player->getGridPosition(grid).y - m_player->getPosition().y);
      }

      if (dist < 8)
      {
        // Find first segment that is occupying the coordinate, and first segment that is leaving the coordinate
        bool collision = segmentController->findSegmentWithGrid(grid) != nullptr;

        if (collision)
        {
          if (!m_collided)
          {
            //m_player->setCollided(true);
            m_player->setSpeed(sf::Vector2f(0.1f, 0.1f));
            m_collided = true;
          }
        }
        else // when there is no collision
        {

        }
      }
    }
  }

  void PlayerController::moveCached()
  {
    // prevent null exception
    if (!m_player)
    {
      return;
    }

    ActorProps::Direction dir = m_player->getDirection(); // if the user has not pressed a key, use the current direction

    // change the direction based on the user's input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      dir = ActorProps::Direction::Left;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      dir = ActorProps::Direction::Right;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      dir = ActorProps::Direction::Up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      dir = ActorProps::Direction::Down;
    }

    // When the player is snapped to the grid, we will check if a direction was cached. If the direction was cached
    // then the player's direction will be set to the cached direction.
    // When the player is set for collision with the edge of the screen width/height, set the direction to None, and reset the cached direction.
    if (m_player->isSnapped())
    {
      if (m_cached != CachedKeyboard::Unknown)
      {
        if (m_cached == CachedKeyboard::Left) dir = ActorProps::Direction::Left;
        else if (m_cached == CachedKeyboard::Right) dir = ActorProps::Direction::Right;
        else if (m_cached == CachedKeyboard::Up) dir = ActorProps::Direction::Up;
        else if (m_cached == CachedKeyboard::Down) dir = ActorProps::Direction::Down;
      }

      const int gridX = m_player->getGrid().x;
      const int gridY = m_player->getGrid().y;

      const bool screenL = (gridX - 1) < 0;
      const bool screenR = (gridX + 1) >= GameProps::PROP_SCREEN_WIDTH / GameProps::PROP_GRID_WIDTH;
      const bool screenU = (gridY - 1) < 0;
      const bool screenD = (gridY + 1) >= GameProps::PROP_SCREEN_HEIGHT / GameProps::PROP_GRID_HEIGHT;

      if ((dir == ActorProps::Direction::Left && (screenL))
          || (dir == ActorProps::Direction::Right && (screenR))
          || (dir == ActorProps::Direction::Up && (screenU))
          || (dir == ActorProps::Direction::Down && (screenD)))
      {
        if ((m_player->getDirection() == ActorProps::Direction::Left && (screenL))
            || (m_player->getDirection() == ActorProps::Direction::Right && (screenR))
            || (m_player->getDirection() == ActorProps::Direction::Up && (screenU))
            || (m_player->getDirection() == ActorProps::Direction::Down && (screenD)))
        {
          m_player->setDirection(ActorProps::Direction::None); // colliding head on with a tile
          m_cached = CachedKeyboard::Unknown;
        }
      }
      else
      {
        m_player->setDirection(dir);
        m_cached = CachedKeyboard::Unknown; // Remove the cached key.
      }
      m_player->updateGrid(m_player->getDirection());
    }
    else
    {
      ActorProps::Direction direction = m_player->getDirection();
      if ((direction == ActorProps::Direction::Left && dir == ActorProps::Direction::Right)
          || (direction == ActorProps::Direction::Right && dir == ActorProps::Direction::Left)
          || (direction == ActorProps::Direction::Up && dir == ActorProps::Direction::Down)
          || (direction == ActorProps::Direction::Down && dir == ActorProps::Direction::Up))
      {
        m_player->moveGridFromDirection(dir);
      }
      else
      {
        if (dir != direction)
        {
          if (dir == ActorProps::Direction::Left)
          {
            m_cached = CachedKeyboard::Left;
          }
          else if (dir == ActorProps::Direction::Right)
          {
            m_cached = CachedKeyboard::Right;
          }
          else if (dir == ActorProps::Direction::Up)
          {
            m_cached = CachedKeyboard::Up;
          }
          else if (dir == ActorProps::Direction::Down)
          {
            m_cached = CachedKeyboard::Down;
          }
        }
        return;
      }
      m_player->setDirection(dir);
      m_cached = CachedKeyboard::Unknown;
    }
  }

  void PlayerController::setSegmentController(SegmentController* controller)
  {
    segmentController = controller;
  }

  void PlayerController::render(sf::RenderWindow &window)
  {
    if (m_player)
    {
      m_player->render(window);
    }
  }
}