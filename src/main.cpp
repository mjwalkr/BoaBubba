/**
 * Created by Michael Walker on 11/26/2016.
 **/

//#include "Game.h"
#include "SegmentControllerTest.h"

void runSegmentControllerTest()
{
  boabubba::SegmentControllerTest segmentControllerTest;
  segmentControllerTest.testTightFollowEmptyTrailMove();
}

void runGame()
{
  boabubba::Game game;
  game.run();
}

int main()
{
  runGame();
  return 0;
}