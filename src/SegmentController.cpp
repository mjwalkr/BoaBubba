/**
 * Created by Michael Walker on 11/26/2016.
 **/

#include "Actor/SegmentController.h"

namespace boabubba
{
  SegmentController::SegmentController()
  {
    init();
  }

  SegmentController::~SegmentController()
  {
    m_head = nullptr;
  }

  const Actor* SegmentController::getTarget()
  {
    return m_target;
  }

  void SegmentController::setTarget(Actor* actor)
  {
    m_target = actor;
  }

  const bool SegmentController::shouldTightFollow() const
  {
    if (!m_head || !m_target)
    {
      return false;
    }

    bool result;

    result = (m_tightFollow || m_head->getGrid().equals(m_target->getGridCurrent()));

    // Previously, 'shouldTightFollow' would fail when the head segment was snapped (ready),
    // because the grid position had NOT yet been updated.
    // Now, we will check if (left, right, up, down) of the grid position is the target's grid current.
    if (!result && isHeadReady())
    {
      // Create a grid object that is adjacent to the head segment's grid position.
      const ActorProps::Direction dir = Actor::directionFor(m_head->getGrid(), m_target->getGridCurrent());
      const Grid adjGrid = m_head->getGrid().getGridAdjacentTo(dir);
      result = adjGrid.equals(m_target->getGridCurrent());
    }

    return result;
  }

  const bool SegmentController::isTightFollow() const
  {
    return m_tightFollow;
  }

  void SegmentController::setHead(Segment* segment)
  {
    if (!m_head)
      m_head = segment;
  }

  const bool SegmentController::isHeadReady() const
  {
    if (!m_head)
    {
      return false;
    }
    return (m_currentFront == 0 && m_head->isSnapped());
  }

  void SegmentController::init()
  {
    // Set the variables to defaults
    m_head = nullptr;

    // Create the segments.
    // head
    std::unique_ptr<Segment> ptr(new Segment(Grid(0, 0), nullptr)); // position, follow
    m_segmentMap[ptr->getGrid().getCoords()] = 1;
    m_segments.emplace_back(std::move(ptr));
    setHead(m_segments.back().get()); // sets the head segment once

    // TODO testing purposes for using only the head segment for front (leading)
    m_head->setFront(true);

    // other
    for (int i = 1; i < 10; ++i)
    {
      ptr.reset(new Segment(Grid(0, 0), m_segments.back().get()));
      m_segmentMap[ptr->getGrid().getCoords()]++;
      m_segments.emplace_back(std::move(ptr));
    }

    // Set the current front 'leader' segment to the 'head' segment.
    m_currentFront = 0;

    m_tightFollow = false;
  }

  void SegmentController::snapAllSegments()
  {
    // When the front segment becomes snapped, all of the other segments should be snapped.
    const Segment* front = m_segments[m_currentFront].get();
    if (front->isSnapped())
    {
      for (auto& itr : m_segments)
      {
        // snap the segment to the grid
        const sf::Vector2i gridPos = itr->getGridPosition(itr->getGrid());
        itr->setPosition(sf::Vector2f(static_cast<float>(gridPos.x), static_cast<float>(gridPos.y)));
        itr->setPosInt(sf::Vector2i(gridPos.x, gridPos.y));
        // reset the dist of the segment so the dirty value will not remain
        itr->setDist(0.f);
        // set the direction (should we update the grid as well..)
        itr->setDirection(ActorProps::Direction::None);
        // reset the segment's front (leading) variable
        itr->setFront(false);

        // update the segment locations map
        refreshSegmentLocations(itr);
      }
      m_currentFront = 0;
    }
  }

  void SegmentController::refreshSegmentLocations(const std::unique_ptr<Segment>& segment)
  {
    // Check if the segment has even moved
    if (segment->getGrid() != segment->getGridCurrent())
    {
      // Check if another segment has already occupied the current grid position
      // Obtain the coordinates of the current grid position
      int coord = segment->getGridCurrent().getCoords();
      if (m_segmentMap.find(coord) != m_segmentMap.end() && m_segmentMap[coord] > 0)
      {
        m_segmentMap[coord]--;
      }
      // Add the segment's new coordinate to the map
      coord = segment->getGrid().getCoords();
      if (m_segmentMap.find(coord) != m_segmentMap.end())
      {
        m_segmentMap[coord]++;
      }
      else
      {
        m_segmentMap[coord] = 1;
      }
    }
  }

  void SegmentController::update()
  {
    for (auto& itr : m_segments)
    {
      // Set the marker for the follow segment.
      // We can't set the marker every time the update method is called, however.
      // Set the marker only when 'itr' is snapped (do not set the head segment's marker here).
      if (itr->getFollow() && itr->isSnapped())
        itr->setMarker(itr->getGrid());

      itr->update();

      // When the segment that (itr) is following is not moving.
      if (itr->isFront())
        m_currentFront = itr->getIndex();
    }
    // Snap the segments when the front segment is snapped.
    snapAllSegments();
  }

  void SegmentController::preUpdate()
  {
    if (!m_head || !m_target) return;

    // Things to consider. When the player is sitting idle, and the snake is on top of the player, the player's current grid is pushed
    // each iteration.
    // When the head segment's grid is equal to the target's grid current, then 'tight follow'
    if (shouldTightFollow())
    {
      moveTightFollow();
    }
    else if (isHeadReady()) // find a path when head segment is front and snapped
    {
      moveOnPath(); // finds the path to the target
    }
  }

  void SegmentController::moveTightFollow()
  {
    m_tightFollow = true; // allow tight follow

    // First check if we should still be in 'tight follow' mode.

    // Note: We might possibly have to handle for the target skipping (moving really fast) grid positions
    // We would need to enqueue all of the grid positions that were skipped.
    if (m_targetTrail.empty())
    {
      m_targetTrail.push(Grid(m_target->getGridCurrent())); // add the target's grid current
    }
    else
    {
      // Add the target's grid current when the target has snapped to grid.
      // We are checking the back of the queue because that will be the most recent grid position from the target.
      if (!m_targetTrail.back().equals(m_target->getGridCurrent()))
      {
        m_targetTrail.push(Grid(m_target->getGridCurrent()));
      }
    }

    if (isHeadReady())
    {
      // When we have snapped to the grid at the front of the queue, dequeue it.
      if (m_head->getGrid().equals(m_targetTrail.front()))
      {
        m_targetTrail.pop();
      }

      ActorProps::Direction dir = Actor::directionFor(m_head->getGridCurrent(), m_head->getGrid());

      if (!m_targetTrail.empty()) // update the grid when there is more
      {
        // todo possible bug: duplicate grid being pushed, this will cause the snake to hault because direction will be None
        dir = Actor::directionFor(m_head->getGrid(), m_targetTrail.front());
      }

      m_head->updateGrid(dir);
      m_head->setDirection(dir);

      // The head uses the current grid because its grid position has been updated.
      // As for the other segments (in the for loop), their grid position has NOT been updated yet, so we
      // need to use the next grid for them.
      m_head->setMarker(m_head->getGridCurrent());
    }
  }

  void SegmentController::moveOnPath()
  {
    int startX = m_head->getGrid().x * GameProps::PROP_GRID_WIDTH; // the starting location of the head segment
    int startY = m_head->getGrid().y * GameProps::PROP_GRID_HEIGHT;

    int endX = getTarget()->getGridCurrent().x * GameProps::PROP_GRID_WIDTH;
    int endY = getTarget()->getGridCurrent().y * GameProps::PROP_GRID_HEIGHT;

    Location start(startX, startY);
    Location end(endX, endY);

    // When we have not found a path to the target.
    if (!m_success)
    {
      if (findPathBFS(start, end))
      {
        m_currLoc = start;
        m_endLoc = end;
        m_success = true;
      }
    }

    // When we have found a path to the player.
    if (m_success)
    {
      // Set our starting point to be our current location.
      start = m_currLoc;

      // Iterate the found path from end to start in order to find
      // the next Location the head segment must move towards.
      Location next = m_endLoc;
      while ((start != m_endLoc) && start != m_path[Location::getCoords(next)])
        next = m_path[Location::getCoords(next)];

      // Set our current Location to be the Location we are heading towards now.
      m_currLoc = next;

      // When we have made it to the end of the path, allow finding another path to the target position.
      if (m_currLoc == m_endLoc)
      {
        m_success = false;
        m_path.clear();
      }

      // Decide the next direction the head segment should move towards.
      ActorProps::Direction dir = ActorProps::Direction::None;
      if (m_head->getGridPosition(m_head->getGrid()).x > m_currLoc.getPosition().x)
        dir = ActorProps::Direction::Left;
      else if (m_head->getGridPosition(m_head->getGrid()).x < m_currLoc.getPosition().x)
        dir = ActorProps::Direction::Right;
      else if (m_head->getGridPosition(m_head->getGrid()).y > m_currLoc.getPosition().y)
        dir = ActorProps::Direction::Up;
      else if (m_head->getGridPosition(m_head->getGrid()).y < m_currLoc.getPosition().y)
        dir = ActorProps::Direction::Down;

      m_head->updateGrid(dir);
      m_head->setDirection(dir);
    }
    else
    {
      // A path could not be found; The head segment will continue to move in the direction
      // it was initially heading in, possibly resulting in a collision.
      // For now, we will just stop the head segment from moving.
      m_head->updateGrid(ActorProps::Direction::None);
      m_head->setDirection(ActorProps::Direction::None);
    }

    // The head uses the current grid because its grid position has been updated.
    // As for the other segments (in the for loop), their grid position has NOT been updated yet, so we
    // need to use the next grid for them.
    m_head->setMarker(m_head->getGridCurrent());
  }

  bool SegmentController::findPathBFS(Location& start, Location& end)
  {
    if (start == end) return false;

    // Check to see if the end location is intersecting a segment.
    // This will prevent the controller from trying to find a path where the player is unreachable.
    // TODO implement this at later time

    std::queue<Location> frontier;
    frontier.push(start);

    std::unordered_map<int, Location> came_from;
    came_from[Location::getCoords(start)] = start;

    while (!frontier.empty())
    {
      Location current = frontier.front();
      frontier.pop();

      if (current == end) // found the target
      {
        m_path = came_from;
        return true;
      }

      // If we have not found the end, find all directions to move towards.
      const int leftPos = current.getPosition().x - GameProps::PROP_GRID_WIDTH;
      const int rightPos = current.getPosition().x + GameProps::PROP_GRID_WIDTH;
      const int topPos = current.getPosition().y - GameProps::PROP_GRID_HEIGHT;
      const int bottomPos = current.getPosition().y + GameProps::PROP_GRID_HEIGHT;

      const Location leftLoc = Location(leftPos, current.getPosition().y);
      const Location rightLoc = Location(rightPos, current.getPosition().y);
      const Location topLoc = Location(current.getPosition().x, topPos);
      const Location bottomLoc = Location(current.getPosition().x, bottomPos);

      int leftSegCol = 0;
      int rightSegCol = 0;
      int topSegCol = 0;
      int bottomSegCol = 0;
      const Grid leftGrid(leftPos / GameProps::PROP_GRID_WIDTH, current.getPosition().y / GameProps::PROP_GRID_HEIGHT);
      const Grid rightGrid(rightPos / GameProps::PROP_GRID_WIDTH, current.getPosition().y / GameProps::PROP_GRID_HEIGHT);
      const Grid topGrid(current.getPosition().x / GameProps::PROP_GRID_WIDTH, topPos / GameProps::PROP_GRID_HEIGHT);
      const Grid bottomGrid(current.getPosition().x / GameProps::PROP_GRID_WIDTH, bottomPos / GameProps::PROP_GRID_HEIGHT);

      if (m_segmentMap.find(leftGrid.getCoords()) != m_segmentMap.end())
      {
        leftSegCol = m_segmentMap[leftGrid.getCoords()];
      }

      if (m_segmentMap.find(rightGrid.getCoords()) != m_segmentMap.end())
      {
        rightSegCol = m_segmentMap[rightGrid.getCoords()];
      }

      if (m_segmentMap.find(topGrid.getCoords()) != m_segmentMap.end())
      {
        topSegCol = m_segmentMap[topGrid.getCoords()];
      }

      if (m_segmentMap.find(bottomGrid.getCoords()) != m_segmentMap.end())
      {
        bottomSegCol = m_segmentMap[bottomGrid.getCoords()];
      }

      const bool left = (leftPos >= 0) && (leftSegCol == 0);
      const bool right = (rightPos < GameProps::PROP_SCREEN_WIDTH) && (rightSegCol == 0);
      const bool top = (topPos >= 0) && (topSegCol == 0);
      const bool bottom = (bottomPos < GameProps::PROP_SCREEN_HEIGHT) && (bottomSegCol == 0);

      std::vector<Location> locations;

      if (left) locations.push_back(leftLoc);
      if (right) locations.push_back(rightLoc);
      if (top) locations.push_back(topLoc);
      if (bottom) locations.push_back(bottomLoc);

      for (Location& next : locations)
      {
        // If the location has not been checked.
        if (!came_from.count(Location::getCoords(next)))
        {
          frontier.push(next);
          came_from[Location::getCoords(next)] = current;
        }
      }
    }
    return false;
  }

  void SegmentController::render(sf::RenderWindow& window)
  {
    for (auto& itr : m_segments)
    {
      //window.draw(*(itr.get())); // Dereference the pointer to obtain reference.
      itr.get()->render(window);
    }
  }
}