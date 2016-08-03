//
//  ContactListener.h
//  PhysicsGame
//
//  Created by Chris Sherlock on 25/07/2016.
//
//

#ifndef ContactListener_h
#define ContactListener_h

#include <stdio.h>
#include "Box2D/Box2D.h"
#include "AppUtils.h"
#include "Ball.h"
#include "Target.h"

class ContactListener : public b2ContactListener
{
public:
    ContactListener(void) {};
    ~ContactListener() {};
    
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact){};
    
private:
    void handleContact(Entity* bodyOne, Entity* bodyTwo);
    void fireCollisionType(Entity* bodyOne, Entity* bodyTwo, int type);
};

#endif /* ContactListener_h */
