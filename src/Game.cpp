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
      playerController.preUpdate();

      segmentController.setTarget(playerController.getPlayer());

      segmentController.preUpdate();

      playerController.update();
      segmentController.update();
      // do something here
    }
  }

  void Game::render()
  {
    window.clear();

    // update entities here
    playerController.render(window);
    segmentController.render(window);

    std::ostringstream ss;
    ss << "Player Grid: (" << playerController.getPlayerGrid().x << ", " << playerController.getPlayerGrid().y << ")";
    debugMessages.addMessage(ss.str(), DebugMessages::LABEL_PLAYER_GRID);
    ss.str("");
    ss << "Player Position: " << playerController.getPlayerPosition().x << ", " << playerController.getPlayerPosition().y << ")";
    debugMessages.addMessage(ss.str(), DebugMessages::LABEL_PLAYER_POSITION);
    ss.str("");
    ss << "Snake Tight Follow: " << segmentController.isTightFollow();
    debugMessages.addMessage(ss.str(), DebugMessages::LABEL_SNAKE_TIGHT_FOLLOW);
    debugMessages.render(window);

    window.display();
  }

  void Game::lateUpdate()
  {

  }
}
