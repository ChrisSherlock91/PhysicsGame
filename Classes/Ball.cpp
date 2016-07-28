//
//  Ball.cpp
//  PhysicsGame
//
//  Created by Chris Sherlock on 27/07/2016.
//
//

#include "Ball.h"
#include "PhysicsManager.h"

Ball::Ball(Vec2 position)
{
    m_position = position;
    m_body = PhysicsManager::getInstance()->createBall(m_position);
    m_body->SetUserData(this);
}

Ball::~Ball()
{
    PhysicsManager::getInstance()->destroyBody(m_body);
}

void Ball::setActive()
{
    m_body->SetType(b2_dynamicBody);
}

void Ball::reset()
{
    PhysicsManager::getInstance()->destroyBody(m_body);
    m_body = PhysicsManager::getInstance()->createBall(m_position);
}
