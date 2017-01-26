//
// Created by Michael Walker on 1/1/2017.
//
// This class represents a grid position, every grid space of size GRID_WIDTH/GRID_HEIGHT counts as a position.
// For example: If GRID_WIDTH = 32 and GRID_HEIGHT = 32, then...
// (0, 0) would have a grid position of (0, 0)
// (1, 0) would have a grid position of (0, 0)
// (32, 0) would have a grid position of (1, 0)
// (64, 32) would have a grid position of (2, 1)
//

#ifndef BOABUBBA_GRID_H
#define BOABUBBA_GRID_H

#include <SFML/System/Vector2.hpp>

#include "GameProps.h"
#include <Actor/ActorProps.h>

namespace boabubba
{
  class Grid : public sf::Vector2i
  {
  public:
    Grid();
    Grid(int x, int y);

    void move(const ActorProps::Direction& direction);

    // Returns a 'dummy' Grid object that is to the (left, right, up, down) direction of 'this' Grid.
    Grid getGridAdjacentTo(const ActorProps::Direction& direction) const;

    const int getCoords() const;

    const bool equals(const Grid& other) const;

    static const bool equals(const Grid& gridA, const Grid& gridB)
    {
      return gridA.x == gridB.x && gridA.y == gridB.y;
    }
  };
}

#endif //BOABUBBA_GRID_H
