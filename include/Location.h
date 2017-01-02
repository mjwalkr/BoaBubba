/**
 * Created by Michael Walker on 11/26/2016.
 *
 * This class is used to represent the grid spaces of the game world.
 * Note: the "position" used for the location is the grid coordinate * grid width/height
 * For example:
 * If the grid = (2, 0), the position you should use for this location is 2 * grid width, 0 * grid height.
 **/

#ifndef BOABUBBA_LOCATION_H
#define BOABUBBA_LOCATION_H

#include <SFML/System/Vector2.hpp>

#include "GameProps.h"

namespace boabubba
{
  class Location
  {
  public:
    Location();

    /**
     *
     * @param x
     * @param y
     */
    Location(const int x, const int y);

    /**
     *
     * @param position
     */
    Location(const sf::Vector2i& position);

    /**
     *
     * @param other
     * @return
     */
    bool operator==(const Location other);

    /**
     *
     * @param other
     * @return
     */
    bool operator!=(const Location other);

    /**
     * Returns the (x,y) position of the location.
     * @return the (x,y) position of the location.
     */
    const sf::Vector2i& getPosition() const;

    /**
     *
     * @param location
     * @return the coordinate of the location represented in a 1D array (row-major).
     */
    static int getCoords(const Location& location);

    /**
     *
     * @param x
     * @param y
     * @return the coordinate of the location represented in a 1D array (row-major).
     */
    static int getCoords(const int x, const int y);

  private:
    sf::Vector2i m_position;
  };
}

#endif //BOABUBBA_LOCATION_H
