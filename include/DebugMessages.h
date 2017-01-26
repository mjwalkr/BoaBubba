//
// Created by Michael Walker on 12/25/2016.
//

#ifndef BOABUBBA_GAMEDEBUG_H
#define BOABUBBA_GAMEDEBUG_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <sstream>
#include <unordered_map>

/**
 * Used for displaying object information and other properties.
 */
namespace boabubba
{
  class DebugMessages
  {
  public:
    static const int LABEL_PLAYER_GRID = 0;
    static const int LABEL_PLAYER_POSITION = 1;
    static const int LABEL_SNAKE_TIGHT_FOLLOW = 2;

    DebugMessages();

    void addMessage(std::string message, const int label); // Adds message to list to be displayed.
    void render(sf::RenderWindow &window); // Prints out the list of messages.

  private:
    sf::Font font;
    std::unordered_map<int, sf::Text> m_messages;
  };
}

#endif //BOABUBBA_GAMEDEBUG_H
