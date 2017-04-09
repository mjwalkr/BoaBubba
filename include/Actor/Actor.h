/**
 * Created by Michael Walker on 11/26/2016.
 *
 * Abstract class used to define all entities in the game.
 **/

#ifndef BOABUBBA_ACTOR_H
#define BOABUBBA_ACTOR_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "GameObject.h"
#include "GameProps.h"
#include "ActorProps.h"
#include "Grid.h"
#include "Location.h"

#include <math.h>

namespace boabubba
{
  class Actor : public GameObject, public sf::Drawable {
  public:
    Actor();
    virtual ~Actor() { }
    void setPosition(const Grid& position);
    void setPosition(const sf::Vector2f& position);
    const sf::Vector2f& getPosition() const;

    void setPositionPrevious(const Grid& position);
    void setPositionPrevious(const sf::Vector2f& position);
    const sf::Vector2f& getPositionPrevious() const;

    void setPosInt(const sf::Vector2i& position);
    const sf::Vector2i& getPosInt() const;

    void setGrid(const Grid& grid);
    const Grid& getGrid() const;

    void setGridCurrent(const Grid& grid);
    const Grid& getGridCurrent() const;

    void setGridPrevious(const Grid& grid);
    const Grid& getGridPrevious() const;

    void moveGridFromDirection(const ActorProps::Direction direction);

    const Grid getGridPosition(const Grid& grid) const;

    void updateGrid(const ActorProps::Direction direction);

    void setDirection(const ActorProps::Direction& direction);

    const ActorProps::Direction& getDirection() const;

    static const ActorProps::Direction directionFor(const Grid& from, const Grid& to);

    void setLocation(const Location& location);

    const Location& getLocation() const;

    void setSpeed(const sf::Vector2f& speed);
    const sf::Vector2f& getSpeed() const;

    const bool isVisible() const;
    const bool isSnapped() const;
    void setSnapped(const bool snapped);
    void snapToGrid();

    void moveGridBased();

    virtual void move();

    virtual void preUpdate() = 0;
    virtual void update() = 0;
    virtual void postUpdate() = 0;
    virtual void render(sf::RenderWindow &window) override;

  protected:
    sf::CircleShape m_sprite;

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Vector2f m_position;
    sf::Vector2f m_positionPrevious;
    sf::Vector2i m_posInt;
    Grid m_grid;
    Grid m_gridPrevious;
    Grid m_gridCurrent;
    sf::Vector2f m_speed;
    ActorProps::Direction m_direction;
    Location m_location;
    bool m_snapped;
    bool m_visible;
  };
}

#endif //BOABUBBA_ACTOR_H
