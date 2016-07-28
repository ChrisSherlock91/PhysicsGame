//
//  Target.h
//  PhysicsGame
//
//  Created by Chris Sherlock on 27/07/2016.
//
//

#ifndef Target_h
#define Target_h

#include <stdio.h>
#include "cocos2d.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;

class Target
{
public:
    Target(Vec2 position, Vec2 size);
    ~Target();
    
private:
    b2Body* m_body;
    Vec2 m_position;
};


#endif /* Target_h */
