//
//  ContactListener.cpp
//  PhysicsGame
//
//  Created by Chris Sherlock on 25/07/2016.
//
//

#include "ContactListener.h"

void ContactListener::BeginContact(b2Contact *contact)
{
    void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyAUserData && bodyBUserData )
        handleContact(static_cast<bodyUserData*>( bodyAUserData ), static_cast<bodyUserData*>( bodyBUserData ) );
}

void ContactListener::handleContact(ContactListener::bodyUserData *bodyOne, ContactListener::bodyUserData *bodyTwo)
{
    if(bodyOne->entityType == EntityType::ET_BALL && bodyTwo->entityType == EntityType::ET_TARGET)
    {
        int k = 0;
    }
    else if(bodyOne->entityType == EntityType::ET_TARGET && bodyTwo->entityType == EntityType::ET_BALL)
    {
        int y = 0;
    }
}