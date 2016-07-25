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

class ContactListener : public b2ContactListener
{
public:
    ContactListener(void) {};
    ~ContactListener() {};
    
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact){};
    
    enum EntityType { ET_BALL = 0, ET_TARGET };
    
    struct bodyUserData
    {
        EntityType entityType;
    };
    bodyUserData* myStruct = new bodyUserData;
    
private:
    
    void handleContact(bodyUserData* bodyOne, bodyUserData* bodyTwo);
    
};

#endif /* ContactListener_h */
