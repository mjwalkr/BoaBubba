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

  void SegmentController::setTarget(const Target& target, Actor* actor, const sf::Vector2i& position)
  {
    m_targetType = target;
    m_targetActor = actor;
    m_targetPosition = position;
  }

  void SegmentController::setHead(Segment* segment)
  {
    if (!m_head)
      m_head = segment;
  }

  void SegmentController::init()
  {

  }

  void SegmentController::update()
  {

  }

  void SegmentController::updateDirection()
  {

  }

  void SegmentController::draw(sf::RenderWindow& window)
  {
    for (auto& itr : m_segments)
    {
      window.draw(*(itr.get())); // Dereference the pointer to obtain reference.
    }
  }
}