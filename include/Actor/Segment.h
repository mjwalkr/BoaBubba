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
    Segment(const Grid& grid, Segment* follow);

    /**
     * @return the segment that 'this' segment will follow.
     */
    Segment* getFollow() const;

    /**
     * @return the index of 'this' segment in the snake's body.
     */
    const int getIndex() const;

    /**
     * @return the current displacement traveled by the segment
     */
    const float getDist() const;

    /**
     * @return the position that the following segment should move towards
     */
    const Grid& getMarker();

    /**
     * Sets the target position the segment following 'this' segment must move towards.
     */
    void setMarker(const Grid& marker);

    /**
     * Sets 'this' segment as the front (leading) segment.
     * @param front
     */
    void setFront(const bool front);

    /**
     * Sets whether the segment has collided with another segment (or target?).
     */
    void setCollided(const bool collided);

    /**
     * Updates the displacement
     * @param dist the displacement traveled by the segment
     */
    void setDist(const float dist);

    /**
     * Update that should be called before, update()
     */
    virtual void preUpdate() override;

    /**
     * Updates the actor.
     */
    virtual void update() override;

    /**
     * Update that should be done after, update()
     */
    virtual void postUpdate() override;

    /**
     * @return whether this segment is the front 'leader' segment.
     */
    const bool isFront();

    /**
     * This method is only useful for the head segment, as only this segment can "collide" with other segments (and targets?).
     * @return whether the segment has collided with another segment.
     */
    const bool isCollided() const;

  private:
    /**
     * Set the index of the segment. The head segment will have an index of 0,
     * while the next segment will have an index of [next segment index + 1].
     */
    void setIndex();

    /**
    * Updates the direction that the segment will move.
    */
    void updateDirection();

    /**
     * Movement logic for the front 'leader' segment. The segment will update its position and displacement.
     * The displacement will be obtained by the following segments in order to update their position and displacement.
     */
    void segmentMoveAsLeader();

    /**
     * Movement logic for segements following the front 'leader' segment. The segment will obtain the displacement from
     * the segment it follows in order to update its position and displacement.
     */
    void segmentMoveAsFollower();

    Segment* m_follow;

    // Holds the position that the following segment should move towards.
    // Note: Using the Actor.getGridCurrent() in place of this variable could cause issues
    // later related to the current grid location being updated before the following segments
    // are able to observe it.
    Grid m_marker;

    // Determines whether this segment is the 'leader' segment of all segments following after it.
    // Note: A segment other than the head will be 'leader' when the segments in front of it are unable to move.
    bool m_front;
    // Determines whether the segment is currently colliding with another segment (or target?). This is used for the head segment only
    bool m_collided;
    int m_index;
    float m_dist; // The displacement of the segment's movement.
  };
}

#endif //BOABUBBA_SEGMENT_H
