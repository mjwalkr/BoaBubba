//
// Created by Michael Walker on 12/31/2016.
//

#ifndef BOABUBBA_ACTORPROPS_H
#define BOABUBBA_ACTORPROPS_H

namespace boabubba
{
  class ActorProps
  {
  public:
    ActorProps() = delete; // cannot instantiate this class

    enum class Direction { None, Left, Right, Up, Down };
  };
}

#endif //BOABUBBA_ACTORPROPS_H
