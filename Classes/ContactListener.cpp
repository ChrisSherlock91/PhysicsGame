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
        handleContact(static_cast<Entity*>( bodyAUserData ), static_cast<Entity*>( bodyBUserData ));
}

void ContactListener::handleContact(Entity* bodyOne, Entity* bodyTwo)
{
    if((bodyOne->getEntityType() == AppUtils::EntityType::ET_BALL && bodyTwo->getEntityType() == AppUtils::ET_TARGET) ||
       (bodyOne->getEntityType() == AppUtils::EntityType::ET_TARGET && bodyTwo->getEntityType() == AppUtils::ET_BALL))
    {
        fireCollisionType(bodyOne, bodyTwo, AppUtils::CollisionType::CT_BALL_TARGET);
    }
}

void ContactListener::fireCollisionType(Entity *bodyOne, Entity *bodyTwo, int type)
{
    bodyOne->collisionOccoured(type);
    bodyTwo->collisionOccoured(type);
}