//
//  PhysicsLayer.cpp
//  PhysicsGame
//
//  Created by Chris Sherlock on 29/06/2016.
//
//

#include "PhysicsLayer.h"

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
    
    this->scheduleUpdate();
    
    // Define the gravity vector.
    b2Vec2 gravity;
    gravity.Set(0, 0);
    //gravity.Set(0, -10.0f);//No gravity
    
    // create a world object, which will hold and simulate the rigid bodies.
    m_world = new b2World(gravity);
    
    setDebugDraw(true);
    
    
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
    float32 timeStep = 1/20.0;      //the length of time passed to simulate (seconds)
    int32 velocityIterations = 8;   //how strongly to correct velocity
    int32 positionIterations = 3;   //how strongly to correct position
    
    m_world->Step( timeStep, velocityIterations, positionIterations);
    
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

void PhysicsLayer::createBox(b2Vec2 position, b2Vec2 size)
{
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
    myBodyDef.position.Set(position.x * PTM, position.y * PTM); //set the starting position
    myBodyDef.angle = 0; //set the starting angle
    
    dynamicBody = m_world->CreateBody(&myBodyDef);
    
    b2PolygonShape boxShape;
    boxShape.SetAsBox(size.x * PTM, size.y * PTM);
    
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.restitution = 0;
    boxFixtureDef.friction = 1;
    dynamicBody->CreateFixture(&boxFixtureDef);
    
    m_world->CreateBody(&myBodyDef);
}

void PhysicsLayer::createFloor(b2Vec2 position, b2Vec2 size)
{
    b2BodyDef myBodyDef;
    myBodyDef.type = b2BodyType::b2_staticBody; //this will be a dynamic body
    myBodyDef.position.Set(position.x * PTM, position.y * PTM); //set the starting position
    myBodyDef.angle = 0; //set the starting angle
    m_floorBody = m_world->CreateBody(&myBodyDef);
    
    b2PolygonShape boxShape;
    boxShape.SetAsBox(size.x * PTM, size.y * PTM);
    
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.restitution = 0;
    boxFixtureDef.friction = 1;
    
    m_floorBody->CreateFixture(&boxFixtureDef);
    
    b2BodyDef bodyDef;
    m_world->CreateBody(&bodyDef);
}


void PhysicsLayer::drawLine(Vec2 lastPos, Vec2 currentPos)
{
    float distance = ccpDistance(lastPos, currentPos);
    if (distance > 1)
    {
        b2BodyDef bd;
        bd.type = b2_staticBody;
        bd.position.Set(0, 0);
        b2Body* body = m_world->CreateBody(&bd);

        b2EdgeShape shape;
        shape.Set(b2Vec2(lastPos.x * PTM, lastPos.y * PTM), b2Vec2(currentPos.x * PTM, currentPos.y * PTM));
        body->CreateFixture(&shape, 0.0f);
    }
}


