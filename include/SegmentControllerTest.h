//
// Created by Michael Walker on 1/27/2017.
//

#ifndef BOABUBBA_SEGMENTCONTROLLERTEST_H
#define BOABUBBA_SEGMENTCONTROLLERTEST_H

#include "Game.h"

namespace boabubba
{
  class SegmentControllerTest
  {
  public:
    // 1. head segment snapped
    // 2. there are no more grids in the target trail
    // 3. head segment sets direction to the direction it was facing before becoming snapped
    // 4. next iteration the target updates its grid
    // 5. head segment not yet snapped and thus continues moving in the direction it previously set
    // 6. once the head segment is snapped, it is misaligned with the trail
    void testTightFollowEmptyTrailMove();
  private:
    Game game;
  };
}

#endif //BOABUBBA_SEGMENTCONTROLLERTEST_H
