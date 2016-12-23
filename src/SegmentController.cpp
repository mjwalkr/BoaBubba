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

  const sf::Vector2i SegmentController::getTargetPosition()
  {
    return m_targetPosition;
  }

  void SegmentController::setTargetPosition(const sf::Vector2i& position)
  {
    m_targetPosition = position;
  }

  void SegmentController::setHead(Segment* segment)
  {
    if (!m_head)
      m_head = segment;
  }

  void SegmentController::init()
  {
    // Set the variables to defaults
    m_head = nullptr;

    // Create the segments.
    // head
    std::unique_ptr<Segment> ptr(new Segment(sf::Vector2i(0, 0), nullptr)); // position, follow
    m_segments.emplace_back(std::move(ptr));
    setHead(m_segments.back().get()); // sets the head segment once

    // TODO testing purposes for using only the head segment for front (leading)
    m_head->setFront(true);

    // other
    for (int i = 1; i < 1; ++i)
    {
      ptr.reset(new Segment(sf::Vector2i(0, 0), m_segments.back().get()));
      m_segments.emplace_back(std::move(ptr));
    }

    // TODO remove, for testing path finding
    setTargetPosition(sf::Vector2i(5, 5));

    // Set the current front 'leader' segment to the 'head' segment.
    m_currentFront = 0;
  }

  void SegmentController::update()
  {
    for (auto& itr : m_segments)
    {
      // Set the marker for the follow segment.
      // We can't set the marker every time the update method is called, however.
      // Option 1: Set the marker only when 'itr' is snapped (do not set the head segment's marker here).
      if (itr->getFollow() && itr->isSnapped())
        itr->setMarker(itr->getGrid());

      itr->update();

      // If the head segment is the front, and is snapped to the grid, snap the segment to the grid.
      // Or, should it be, when the front segment becomes snapped, all of the other segments should be snapped.
    }
  }

  void SegmentController::preUpdate()
  {
    if (!m_head) return;

    if (m_head->isSnapped())
      moveOnPath(); // finds the path to the target
  }

  void SegmentController::moveOnPath()
  {
    int startX = m_head->getGrid().x * GameProps::PROP_GRID_WIDTH; // the starting location of the head segment
    int startY = m_head->getGrid().y * GameProps::PROP_GRID_HEIGHT;

    int endX = getTargetPosition().x * GameProps::PROP_GRID_WIDTH;
    int endY = getTargetPosition().y * GameProps::PROP_GRID_HEIGHT;

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
      boabubba::Direction dir = boabubba::Direction::None;
      if (m_head->getGridPosition(m_head->getGrid()).x > m_currLoc.getPosition().x)
        dir = boabubba::Direction::Left;
      else if (m_head->getGridPosition(m_head->getGrid()).x < m_currLoc.getPosition().x)
        dir = boabubba::Direction::Right;
      else if (m_head->getGridPosition(m_head->getGrid()).y > m_currLoc.getPosition().y)
        dir = boabubba::Direction::Up;
      else if (m_head->getGridPosition(m_head->getGrid()).y < m_currLoc.getPosition().y)
        dir = boabubba::Direction::Down;

      m_head->updateGrid(dir);
      m_head->setDirection(dir);
    }
    else
    {
      // A path could not be found; The head segment will continue to move in the direction
      // it was initially heading in, possibly resulting in a collision.
      // For now, we will just stop the head segment from moving.
      m_head->updateGrid(boabubba::Direction::None);
      m_head->setDirection(boabubba::Direction::None);
    }

    // The head uses the grid previous because its grid position has been updated.
    // As for the other segments (in the for loop), their grid position has NOT been updated yet, so we
    // need to use the current grid for them.
    m_head->setMarker(m_head->getGridPrevious());
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

      const bool left = (leftPos >= 0);
      const bool right = (rightPos < GameProps::PROP_SCREEN_WIDTH);
      const bool top = (topPos >= 0);
      const bool bottom = (bottomPos < GameProps::PROP_SCREEN_HEIGHT);

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

  void SegmentController::draw(sf::RenderWindow& window)
  {
    for (auto& itr : m_segments)
    {
      window.draw(*(itr.get())); // Dereference the pointer to obtain reference.
    }
  }
}