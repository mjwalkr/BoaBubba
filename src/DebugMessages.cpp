//
// Created by Michael Walker on 12/25/2016.
//

#include "DebugMessages.h"

namespace boabubba
{

  DebugMessages::DebugMessages()
  {

  }

  void DebugMessages::addMessage(std::string message, const int label)
  {
    if (font.loadFromFile("arial.ttf")) {
      sf::Text text;
      text.setFont(font);
      text.setCharacterSize(12);
      text.setString(message);
      m_messages[label] = text;
    }
  }

  void DebugMessages::render(sf::RenderWindow &window)
  {
    int y = 0;
    for (auto &itr : m_messages)
    {
      sf::Text& txt = itr.second;
      txt.setPosition(0, y++ * 16);
      window.draw(itr.second);
    }
  }
}