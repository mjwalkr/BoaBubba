/**
 * Created by Michael Walker on 11/26/2016.
 *
 * This is class represents a segment of the snake. Each segment contain
 * a pointer to the previous segment that makes up the snake's body.
 **/

#ifndef BOABUBBA_SEGMENT_H
#define BOABUBBA_SEGMENT_H

#include "Actor/Actor.h"

namespace boabubba
{
  class Segment : public Actor
  {
  public:
    /**
     * Creates a segment and specifies the segment that 'this' segment will follow,
     * and 'this' segment's position.
     * @param position the grid position of the segment.
     * @param follow the segment 'this' segment will follow.
     */
    Segment(const sf::Vector2i& position, Segment* follow);

    /**
     *
     * @return the segment that 'this' segment will follow.
     */
    Segment* getFollow() const;

    /**
     *
     * @return the index of 'this' segment in the snake's body.
     */
    const int getIndex() const;

    /**
     * Updates the actor.
     */
    virtual void update() override;

    /**
     * Updates the direction that the segment will move.
     */
    void updateDirection();

  private:
    Segment* m_follow;
    int m_index;
  };
}

#endif //BOABUBBA_SEGMENT_H
