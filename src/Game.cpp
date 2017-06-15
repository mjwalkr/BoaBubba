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

    playerController.setSegmentController(&segmentController);
    segmentController.setTarget(playerController.getPlayer());
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

      segmentController.preUpdate();

      playerController.update();
      segmentController.update();
      // do something here
      playerController.postUpdate();
      segmentController.postUpdate();
    }
  }

  void Game::render()
  {
    window.clear();

    for (int i = 32; i < 480; i += 32) {
      sf::Vertex line[] = {
          sf::Vertex(sf::Vector2f(0, i)),
          sf::Vertex(sf::Vector2f(640, i))
      };
      window.draw(line, 2, sf::Lines);
    }

    for (int i = 32; i < 640; i += 32) {
      sf::Vertex line[] = {
          sf::Vertex(sf::Vector2f(i, 0)),
          sf::Vertex(sf::Vector2f(i, 480))
      };
      window.draw(line, 2, sf::Lines);
    }

    // update entities here
    playerController.render(window);
    segmentController.render(window);

    std::ostringstream ss;
    //ss << "Player Grid: (" << playerController.getPlayerGrid().x << ", " << playerController.getPlayerGrid().y << ")";
    //debugMessages.addMessage(ss.str(), DebugMessages::LABEL_PLAYER_GRID);
    //ss.str("");
    //ss << "Player Position: " << playerController.getPlayerPosition().x << ", " << playerController.getPlayerPosition().y << ")";
    //debugMessages.addMessage(ss.str(), DebugMessages::LABEL_PLAYER_POSITION);
    //ss.str("");
    //ss << "Snake Tight Follow: " << segmentController.isTightFollow();
    //debugMessages.addMessage(ss.str(), DebugMessages::LABEL_SNAKE_TIGHT_FOLLOW);
    //ss.str("");

    ss << "Target Trail:\n";
    std::queue<Grid> trail = segmentController.getTargetTrail();
    while (!trail.empty())
    {
      ss << "[ " << trail.front().x << ", " << trail.front().y << " ]\n";
      trail.pop();
    }
    debugMessages.addMessage(ss.str(), DebugMessages::LABEL_SNAKE_TARGET_TRAIL);

    debugMessages.render(window);

    window.display();
  }

  void Game::lateUpdate()
  {

  }
}
