//
//  PhysicsManager.cpp
//  PhysicsGame
//
//  Created by Chris Sherlock on 28/07/2016.
//
//

#include "PhysicsManager.h"
#include "ContactListener.h"

#define MTP 32.0
#define PTM 1/32.0f

PhysicsManager* PhysicsManager::ms_pInstance = 0;

PhysicsManager::PhysicsManager() : m_shouldClearLevel(false)
{
    b2Vec2 gravity;
    gravity.Set(0, -7);
    
    m_world = new b2World(gravity);
    
    ContactListener* listener = new ContactListener();
    m_world->SetContactListener(listener);
}

PhysicsManager::~PhysicsManager()
{
    
}

PhysicsManager* PhysicsManager::getInstance()
{
    if(ms_pInstance == 0)
        ms_pInstance = new PhysicsManager();
    return ms_pInstance;
}

void PhysicsManager::releaseInstance()
{
    if(ms_pInstance != 0)
    {
        delete ms_pInstance;
        ms_pInstance = 0;
    }
}

void PhysicsManager::update(float dt)
{
    //float32 timeStep = 1/20.0;      //the length of time passed to simulate (seconds)
    int32 velocityIterations = 8;   //how strongly to correct velocity
    int32 positionIterations = 1;   //how strongly to correct position
        
    m_world->Step(dt, velocityIterations, positionIterations);
        
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    m_world->Step(dt, velocityIterations, positionIterations);
        
    // Iterate over the bodies in the physics world
    for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL)
        {
            //            // Synchronize the AtlasSprites position and rotation with the corresponding body
            //            Sprite* myActor = (Sprite*)b->GetUserData();
            //            myActor->setPosition( Vec2( b->GetPosition().x * 32, b->GetPosition().y * 32) );
            //            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }
    }
        
    checkForClearLevel();
}

void PhysicsManager::resetLevel()
{
    m_shouldClearLevel = true;
}

void PhysicsManager::checkForClearLevel()
{
    if(m_shouldClearLevel)
    {
        for(std::vector<b2Body*>::iterator it = m_lineBodies.begin(); it != m_lineBodies.end(); ++it)
        {
            m_world->DestroyBody((*it));
        }
        m_lineBodies.clear();
        m_shouldClearLevel = false;
    }
}

void PhysicsManager::drawLine(std::vector<std::pair<Vec2, Vec2>> points)
{
    b2BodyDef bd;
    bd.type = b2_staticBody;
    bd.position.Set(0 * PTM, 0 * PTM);
    b2Body* body = m_world->CreateBody(&bd);
    m_lineBodies.push_back(body);
    
    for(std::vector<std::pair<Vec2, Vec2>>::iterator it = points.begin(); it != points.end(); ++it)
    {
        b2EdgeShape shape;
        shape.Set(b2Vec2((*it).first.x / PTM, (*it).first.y / PTM), b2Vec2((*it).second.x / PTM, (*it).second.y / PTM));
        body->CreateFixture(&shape, 0.0f);
    }
}

b2Body* PhysicsManager::createStaticBody(Vec2 position, Vec2 size)
{
    b2Body* body;
    b2BodyDef myBodyDef;
    myBodyDef.type = b2BodyType::b2_staticBody; //this will be a dynamic body
    myBodyDef.position.Set(position.x * PTM, position.y * PTM); //set the starting position
    myBodyDef.angle = 0; //set the starting angle
    body = m_world->CreateBody(&myBodyDef);
    
    b2PolygonShape boxShape;
    boxShape.SetAsBox(size.x * PTM, size.y * PTM);
    
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.restitution = 0;
    boxFixtureDef.friction = 1;
    
    body->CreateFixture(&boxFixtureDef);
    
    b2BodyDef bodyDef;
    m_world->CreateBody(&bodyDef);
    return body;
}

b2Body* PhysicsManager::createBall(Vec2 position)
{
    b2Body* bombBody;
    b2BodyDef myBodyDef;
    myBodyDef.type = b2BodyType::b2_kinematicBody;
    myBodyDef.position.Set(position.x * PTM, position.y * PTM);
    bombBody = m_world->CreateBody(&myBodyDef);
    
    AppUtils::BodyUserData* myStruct = new AppUtils::BodyUserData;
    myStruct->entityType = AppUtils::EntityType::ET_BALL;
    bombBody->SetUserData(myStruct);
    
    b2CircleShape circleShape;
    circleShape.m_radius = 10 * PTM;
    
    b2FixtureDef circleFixtureDef;
    circleFixtureDef.shape = &circleShape;
    circleFixtureDef.density = 1;
    circleFixtureDef.restitution = 0;
    circleFixtureDef.friction = 1;
    
    bombBody->CreateFixture(&circleFixtureDef);
    
    b2BodyDef bodyDef;
    m_world->CreateBody(&bodyDef);
    return bombBody;
}

void PhysicsManager::destroyBody(b2Body *body)
{
    m_world->DestroyBody(body);
}
