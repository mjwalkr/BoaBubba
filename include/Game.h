//
// Created by seyuu_000 on 11/28/2016.
//

#ifndef BOABUBBA_GAME_H
#define BOABUBBA_GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "../include/Timestep.h"
#include "../include/GameProps.h"

namespace boabubba
{
  class Game
  {
  public:
    Game();

    void run();
    void update();
    void render();
    void lateUpdate();

  private:
    sf::RenderWindow window;
    kairos::Timestep timeStep;
    const float dt;
  };
}

#endif //BOABUBBA_GAME_H
