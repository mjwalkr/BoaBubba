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

  void Grid::move(const ActorProps::Direction& direction)
  {
    switch(direction)
    {
      case ActorProps::Direction::Left: x--; break;
      case ActorProps::Direction::Right: x++; break;
      case ActorProps::Direction::Up: y--; break;
      case ActorProps::Direction::Down: y++; break;
      default: break;
    }
  }

  Grid Grid::getGridAdjacentTo(const ActorProps::Direction &direction) const
  {
    Grid dummyGrid(*this);
    dummyGrid.move(direction);

    return dummyGrid;
  }

  const int Grid::getCoords() const
  {
    return (x * GameProps::PROP_SCREEN_WIDTH_IN_GRIDS) + y;
  }

  const bool Grid::equals(const Grid &other) const
  {
    return x == other.x && y == other.y;
  }
}
