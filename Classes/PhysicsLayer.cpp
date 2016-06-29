//
//  PhysicsLayer.cpp
//  PhysicsGame
//
//  Created by Chris Sherlock on 29/06/2016.
//
//

#include "PhysicsLayer.h"
#include "BodyFactory.h"

#define MTP 30
#define PTM 1/30.0f

PhysicsLayer* PhysicsLayer::createLayer()
{
    // 'layer' is an autorelease object
    auto layer = PhysicsLayer::create();
    
    // return the scene
    return layer;
}

// on "init" you need to initialize your instance
bool PhysicsLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->scheduleUpdate();
    
    // Define the gravity vector.
    b2Vec2 gravity;
    gravity.Set(0, -10.0f);//No gravity
    
    // create a world object, which will hold and simulate the rigid bodies.
    m_world = new b2World(gravity);
    
    setDebugDraw(true);
    
    BodyFactory::createFloor(b2Vec2(0, visibleSize.height * 0.1), b2Vec2(visibleSize.width, visibleSize.height * 0.1), m_world);
    BodyFactory::createBox(b2Vec2(visibleSize.width / 2, visibleSize.height / 2), b2Vec2(10,10), m_world);
    
    return true;
}
void PhysicsLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
    cocos2d::Layer::draw(renderer, transform, flags);
    
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    m_world->DrawDebugData();
    
    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void PhysicsLayer::update(float delta)
{
    int velocityIterations = 8;
    int positionIterations = 3;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    m_world->Step(delta, velocityIterations, positionIterations);
    
    // Iterate over the bodies in the physics world
    for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL)
        {
            // Synchronize the AtlasSprites position and rotation with the corresponding body
            Sprite* myActor = (Sprite*)b->GetUserData();
            myActor->setPosition( Vec2( b->GetPosition().x * 32, b->GetPosition().y * 32) );
            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }
    }
}

void PhysicsLayer::setDebugDraw(bool set)
{
    if(set)
    {
        uint32 flags = 0;
        flags += b2Draw::e_shapeBit;
        flags += b2Draw::e_jointBit;
        flags += b2Draw::e_aabbBit;
        flags += b2Draw::e_pairBit;
        flags += b2Draw::e_centerOfMassBit;
        flags += b2Draw::e_aabbBit;
        auto debugDraw = new GLESDebugDraw(32);
        debugDraw->SetFlags(flags);
        m_world->SetDebugDraw(debugDraw);
        m_world->DrawDebugData();
    }
    else
    {
        auto debugDraw = new GLESDebugDraw(32);
        debugDraw->SetFlags(0);
        m_world->SetDebugDraw(debugDraw);
    }
}


