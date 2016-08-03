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
#include "AppUtils.h"

using namespace cocos2d;

class Target : public Entity
{
public:
    Target(Vec2 position, Vec2 size);
    ~Target();

    void collisionOccoured(int type);
    int getEntityType();
    
private:
    b2Body* m_body;
    Vec2 m_position;
};


#endif /* Target_h */
