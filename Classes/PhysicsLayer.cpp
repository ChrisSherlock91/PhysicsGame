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
    gravity.Set(0, -10.0f);//No gravity
    
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
    int velocityIterations = 5;
    int positionIterations = 5;
    
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
    
    b2Body* dynamicBody = m_world->CreateBody(&myBodyDef);
    
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
    b2Body* floorBody = m_world->CreateBody(&myBodyDef);
    
    b2PolygonShape boxShape;
    boxShape.SetAsBox(size.x * PTM, size.y * PTM);
    
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.restitution = 0;
    boxFixtureDef.friction = 1;
    
    floorBody->CreateFixture(&boxFixtureDef);
    
    b2BodyDef bodyDef;
    m_world->CreateBody(&bodyDef);
}

void PhysicsLayer::createArrow(b2Vec2 position)
{
    float angle = 70;
    b2PolygonShape polygonShape;
    b2Vec2 vertices[4];
    vertices[0].Set(-1.4f, 0);
    vertices[1].Set(0, -0.1f );
    vertices[2].Set(0.6f, 0);
    vertices[3].Set(0, 0.1f);
    polygonShape.Set(vertices, 4);
    b2BodyDef bodyDef;
    bodyDef.angle = angle;
    bodyDef.position.Set(200 * PTM, 200 * PTM);
    bodyDef.type = b2BodyType::b2_dynamicBody;
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygonShape;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.5f;
    
    b2Body *body = m_world->CreateBody(&bodyDef);
    body->CreateFixture(&fixtureDef);
    body->SetLinearVelocity(b2Vec2(2,2));
}



