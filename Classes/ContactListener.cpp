//
//  ContactListener.cpp
//  PhysicsGame
//
//  Created by Chris Sherlock on 25/07/2016.
//
//

#include "ContactListener.h"
#include "Ball.h"
#include "Target.h"

void ContactListener::BeginContact(b2Contact *contact)
{
    void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyAUserData && bodyBUserData )
        handleContact(static_cast<AppUtils::BodyUserData*>( bodyAUserData ), static_cast<AppUtils::BodyUserData*>( bodyBUserData ) );
}

void ContactListener::handleContact(AppUtils::BodyUserData *bodyOne, AppUtils::BodyUserData *bodyTwo)
{
    if(bodyOne->entityType == AppUtils::EntityType::ET_BALL && bodyTwo->entityType == AppUtils::EntityType::ET_TARGET)
    {
       
    }
    else if(bodyOne->entityType == AppUtils::EntityType::ET_TARGET && bodyTwo->entityType == AppUtils::EntityType::ET_BALL)
    {
        
    }
}