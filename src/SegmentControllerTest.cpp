//
// Created by Michael Walker on 1/27/2017.
//

#include "SegmentControllerTest.h"

namespace boabubba
{
  void SegmentControllerTest::testTightFollowEmptyTrailMove()
  {
    // setup
    PlayerController *playerController = game.getPlayerController();
    Player *player = playerController->getPlayer();
    player->setPosition(Grid(20, 10));

    SegmentController *segmentController = game.getSegmentController();
    segmentController->setSegmentsPosition(Grid(21, 10));
    Segment* head = segmentController->getHead();
    head->setDirection(ActorProps::Direction::Up);
    head->updateGrid(ActorProps::Direction::Up);
    head->setMarker(head->getGridCurrent());

    segmentController->setTightFollow(true);
    std::queue<Grid> trail;
    trail.push(Grid(player->getGridCurrent()));
    segmentController->setTargetTrail(trail);

    // start test
    game.run();
  }
}