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
    
    struct BodyUserData
    {
        EntityType entityType;
    };
    
private:

    
    
};

#endif /* AppUtils_h */
