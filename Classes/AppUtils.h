//
//  AppUtils.h
//  PhysicsGame
//
//  Created by Chris Sherlock on 25/07/2016.
//
//

#ifndef AppUtils_h
#define AppUtils_h

#include <stdio.h>
#include "cocos2d.h"

class AppUtils
{
public:
    enum EntityType { ET_BALL = 0, ET_TARGET };
    enum CollisionType { CT_BALL_TARGET = 0 };

private:
    
};

// Used for collision callbacks
class Entity
{
public:
    virtual int getEntityType() = 0;
    virtual void collisionOccoured(int type) = 0;
};

#endif /* AppUtils_h */
