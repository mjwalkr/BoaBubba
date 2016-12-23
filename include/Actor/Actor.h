/**
 * Created by Michael Walker on 11/26/2016.
 *
 * Abstract class used to define all entities in the game.
 **/

#ifndef BOABUBBA_ACTOR_H
#define BOABUBBA_ACTOR_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "GameObject.h"
#include "GameProps.h"

#include <math.h>

namespace boabubba
{
  enum class Direction { None, Left, Right, Up, Down };

  class Actor : public GameObject, public sf::Drawable {
  public:
    Actor();
    virtual ~Actor() { }
    void setPosition(const sf::Vector2i& position);
    void setPosition(const sf::Vector2f& position);
    const sf::Vector2f& getPosition() const;

    void setPositionPrevious(const sf::Vector2i& position);
    void setPositionPrevious(const sf::Vector2f& position);
    const sf::Vector2f& getPositionPrevious() const;

    void setPosInt(const sf::Vector2i& position);
    const sf::Vector2i& getPosInt() const;

    void setGrid(const sf::Vector2i& grid);
    const sf::Vector2i& getGrid() const;

    void setGridPrevious(const sf::Vector2i& grid);
    const sf::Vector2i& getGridPrevious() const;

    const sf::Vector2i getGridPosition(const sf::Vector2i& grid) const;

    void updateGrid(const Direction direction);

    void setDirection(const Direction& direction);
    const Direction& getDirection() const;

    void setSpeed(const sf::Vector2f& speed);
    const sf::Vector2f& getSpeed() const;

    const bool isVisible() const;
    const bool isSnapped() const;

    void moveGridBased();

    virtual void move();

    virtual void update() = 0;
    virtual void render(sf::RenderWindow &window) override;

  protected:
    sf::CircleShape m_sprite;

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Vector2f m_position;
    sf::Vector2f m_positionPrevious;
    sf::Vector2i m_posInt;
    sf::Vector2i m_grid;
    sf::Vector2i m_gridPrevious;
    sf::Vector2f m_speed;
    Direction m_direction;

    bool m_visible;
  };
}

#endif //BOABUBBA_ACTOR_H
