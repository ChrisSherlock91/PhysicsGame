//
//  BodyFactory.h
//  PhysicsGame
//
//  Created by Chris Sherlock on 29/06/2016.
//
//

#ifndef BodyFactory_h
#define BodyFactory_h

#include <stdio.h>
#include "Box2D/Box2D.h"

#pragma once
class BodyFactory
{
public:
    BodyFactory(void);
    ~BodyFactory(void);
    
    static void createBox(b2Vec2 position, b2Vec2 size, b2World *world);
    static void createFloor(b2Vec2 position, b2Vec2 size, b2World *world);
    
};


#endif /* BodyFactory_h */
