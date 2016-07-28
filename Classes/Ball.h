//
//  Ball.h
//  PhysicsGame
//
//  Created by Chris Sherlock on 27/07/2016.
//
//

#ifndef Ball_h
#define Ball_h

#include <stdio.h>
#include "cocos2d.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;

class Ball : cocos2d::Sprite
{
public:
    Ball(Vec2 position);
    ~Ball();
    
    void reset();
    void setActive();
    
private:
    b2Body* m_body;
    Vec2 m_position;
};

#endif /* Ball_h */
