//
// Created by Michael Walker on 1/1/2017.
//

#include "Grid.h"

namespace boabubba
{
  Grid::Grid()
  : sf::Vector2i()
  {
  }

  Grid::Grid(int x, int y)
  : sf::Vector2i(x, y)
  {
  }

  const int Grid::getCoords() const
  {
    return (x * GameProps::PROP_SCREEN_WIDTH_IN_GRIDS) + y;
  }
}
