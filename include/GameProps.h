/**
 * Created by Michael Walker on 11/26/2016.
 *
 * Holds properties related to the game.
 **/

#ifndef BOABUBBA_GAMEPROPS_H
#define BOABUBBA_GAMEPROPS_H

namespace boabubba
{
  class GameProps
  {
  public:
    static const int PROP_SCREEN_WIDTH = 640;
    static const int PROP_SCREEN_HEIGHT = 480;
    static const int PROP_GRID_WIDTH = 32;
    static const int PROP_GRID_HEIGHT = 32;
    static const int PROP_SCREEN_WIDTH_IN_GRIDS = 640 / 32; // PROP_SCREEN_WIDTH / PROP_GRID_WIDTH
  };
}

#endif //BOABUBBA_GAMEPROPS_H
