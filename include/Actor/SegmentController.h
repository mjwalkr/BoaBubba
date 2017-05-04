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
#include <list>
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

    Segment* getHead();

    void setSegmentsPosition(Grid grid);

    void setTarget(Actor* actor);
    const Actor* getTarget();

    void setTightFollow(bool tightFollow);
    const bool isTightFollow() const;

    void setTargetTrail(std::queue<Grid> trail);
    std::queue<Grid> getTargetTrail() const;

    const Segment* findSegmentWithGrid(const Grid grid);

    /**
     * Prepares the head segment for movement. Decides which type of movement the head segment
     * should perform (follow target's calculated path; follow target's immediate path)
     */
    void preUpdate();
    void update();
    void postUpdate();
    // TODO - this method is temporary, as a tree structure will be used to draw the actors.
    void render(sf::RenderWindow& window);

  private:
    void init();
    void setHead(Segment* segment);
    void snapAllSegments();
    void refreshSegmentLocations(const std::unique_ptr<Segment>& segment);

    const bool isHeadReady() const;
    const bool shouldTightFollow() const;
    void moveTightFollow();

    /**
    * Calls findPathXXX method to calculate the path to the target and set's the head
    * segment's properties in order to arrive to the destination.
    */
    void moveOnPath();
    bool findPathBFS(Location& start, Location& end);

    Actor* m_target; // this position MUST be a grid position.

    Segment* m_head;

    int m_currentFront; // Holds the index of the current front 'leader' segment.

    bool m_tightFollow; // holds whether the snake will trail the target
    bool m_restrictTargetTrail; // prevents adding elements to the target trail
    std::queue<Grid> m_targetTrail; // hold the trail of grid positions traversed by the target
    std::queue<Grid> m_targetTrailPrevious; // holds the last N grid positions that were popped.

    // path finding helper variables
    std::unordered_map<int, Location> m_path;
    Location m_currLoc; // represents the current iteration (Location) in the found path.
    Location m_endLoc; // represents the end (Location) of the found path.
    bool m_success; // holds whether we have found a path to the target position.

    // collision variables
    bool m_collided;

    std::vector<std::unique_ptr<Segment>> m_segments;
    // holds map of segments; used for locating where segments are on the game field. each position mapped, holds the number of segments occupying the position
    std::unordered_map<int, int> m_segmentMap;
  };
}


#endif //BOABUBBA_SEGMENTCONTROLLER_H
