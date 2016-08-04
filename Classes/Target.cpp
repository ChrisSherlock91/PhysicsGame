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
        m_emitter = ParticleExplosion::create();
        m_emitter->setTexture( Director::getInstance()->getTextureCache()->addImage("stars.png"));
        m_emitter->setAutoRemoveOnFinish(true);
        m_emitter->setPosition(m_position);
        m_emitter->setTotalParticles(500);
        m_emitter->setLife(1.5);
        m_emitter->setSpeed(500);
        this->addChild(m_emitter, 10);
    }
}


