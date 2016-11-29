/**
 * Created by Michael Walker on 11/26/2016.
 *
 * This is class represents the controller object for the snake segments.
 * A separate class was created in order to prevent the other segments from
 * acquiring unneeded variables and data structures.
 * The segment controller will control the flow of all the other segments.
 **/

#ifndef BOABUBBA_SEGMENTCONTROLLER_H
#define BOABUBBA_SEGMENTCONTROLLER_H

#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <functional>

#include "Actor.h"
#include "Segment.h"
#include "Location.h"


namespace boabubba
{
  enum class Target { None, Actor, Position };
  class SegmentController
  {
  public:
    SegmentController();
    ~SegmentController();

    void setTarget(const Target& target, Actor* actor, const sf::Vector2i& position);
    void setHead(Segment* segment);

    void init();
    void update();
    void updateDirection();
    // TODO - this method is temporary, as a tree structure will be used to draw the actors.
    void draw(sf::RenderWindow& window);

    bool findPathBFS(const Location& start, const Location& end);

  private:
    Target m_targetType;
    Actor* m_targetActor;
    sf::Vector2i m_targetPosition;

    Segment* m_head;

    std::vector<std::unique_ptr<Segment>> m_segments;
  };
}


#endif //BOABUBBA_SEGMENTCONTROLLER_H
