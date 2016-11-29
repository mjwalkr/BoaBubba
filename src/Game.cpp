/**
 * Created by Michael Walker on 11/28/2016.
 **/

#include "Game.h"

namespace boabubba
{
  Game::Game()
      : dt(timeStep.getStepAsFloat())
  {
    window.create(sf::VideoMode(GameProps::PROP_SCREEN_WIDTH, GameProps::PROP_SCREEN_HEIGHT, 32), "BoaBubba");
  }

  void Game::run()
  {
    while (window.isOpen())
    {
      update();
      render();
      lateUpdate();
    }
  }

  void Game::update()
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    timeStep.addFrame();
    while (timeStep.isUpdateRequired())
    {
      // do something here
    }
  }

  void Game::render()
  {
    window.clear();

    // update entities here

    window.display();
  }

  void Game::lateUpdate()
  {

  }
}
