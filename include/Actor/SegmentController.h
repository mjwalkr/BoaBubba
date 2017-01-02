/**
 * Created by Michael Walker on 11/26/2016.
 *
 * This is class represents the controller object for the snake segments.
 * A separate class was created in order to prevent the other segments from
 * acquiring unneeded variables and data structures.
 * The segment controller will control the flow of all the other segments.
 *
 * Responsibilities:
 *
 * 1. Calculating the path to the target.
 * 2. Setting a segment as the 'leader' (front segment).
 *
 **/

#ifndef BOABUBBA_SEGMENTCONTROLLER_H
#define BOABUBBA_SEGMENTCONTROLLER_H

#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <queue>
#include <functional>
#include <unordered_map>

#include "Actor.h"
#include "Segment.h"
#include "Location.h"
#include "GameProps.h"


namespace boabubba
{
  class SegmentController
  {
  public:
    SegmentController();
    ~SegmentController();

    const sf::Vector2i getTargetPosition();

    void setTargetPosition(const sf::Vector2i& position);

    /**
     * Prepares the head segment for movement. Decides which type of movement the head segment
     * should perform (follow target's calculated path; follow target's immediate path)
     */
    void preUpdate();
    void update();
    // TODO - this method is temporary, as a tree structure will be used to draw the actors.
    void render(sf::RenderWindow& window);

  private:
    void init();
    void setHead(Segment* segment);
    void snapAllSegments();
    void refreshSegmentLocations(const std::unique_ptr<Segment>& segment);
    /**
    * Calls findPathXXX method to calculate the path to the target and set's the head
    * segment's properties in order to arrive to the destination.
    */
    void moveOnPath();
    bool findPathBFS(Location& start, Location& end);

    sf::Vector2i m_targetPosition; // this position MUST be a grid position.

    Segment* m_head;

    int m_currentFront; // Holds the index of the current front 'leader' segment.

    // path finding helper variables
    std::unordered_map<int, Location> m_path;
    Location m_currLoc; // represents the current iteration (Location) in the found path.
    Location m_endLoc; // represents the end (Location) of the found path.
    bool m_success; // holds whether we have found a path to the target position.

    std::vector<std::unique_ptr<Segment>> m_segments;
    // holds map of segments; used for locating where segments are on the game field. each position mapped, holds the number of segments occupying the position
    std::unordered_map<int, int> m_segmentMap;
  };
}


#endif //BOABUBBA_SEGMENTCONTROLLER_H
