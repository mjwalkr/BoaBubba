//
// Created by Michael Walker on 12/31/2016.
//

#ifndef BOABUBBA_PLAYER_H
#define BOABUBBA_PLAYER_H

#include "Actor.h"

namespace boabubba
{
  class Player : public Actor
  {
  public:
    Player(const Grid& startPosition);

    void preUpdate() override;
    void update() override;
    void postUpdate() override;

    virtual void render(sf::RenderWindow &window) override;

    void setGround(const bool ground);

  private:
    bool m_ground;
  };
}

#endif //BOABUBBA_PLAYER_H
