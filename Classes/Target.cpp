//
//  Target.cpp
//  PhysicsGame
//
//  Created by Chris Sherlock on 27/07/2016.
//
//

#include "Target.h"
#include "PhysicsManager.h"

Target::Target(Vec2 position, Vec2 size)
{
    m_position = position;
    m_body = PhysicsManager::getInstance()->createStaticBody(position, size);
    m_body->SetUserData((Entity*)this);
}

Target::~Target()
{
    PhysicsManager::getInstance()->destroyBody(m_body);
}

int Target::getEntityType()
{
    return AppUtils::EntityType::ET_TARGET;
}

void Target::collisionOccoured(int type)
{
    if(type == AppUtils::CollisionType::CT_BALL_TARGET)
    {
        ParticleExplosion* explosion = ParticleExplosion::create();
        explosion->setTexture( Director::getInstance()->getTextureCache()->addImage("stars.png"));
        explosion->setAutoRemoveOnFinish(true);
        explosion->setPosition(m_position);
        explosion->setTotalParticles(500);
        explosion->setLife(1.5);
        explosion->setSpeed(500);
        this->addChild(explosion, 10);
    }
}


