//
//  BodyFactory.cpp
//  PhysicsGame
//
//  Created by Chris Sherlock on 29/06/2016.
//
//

#include "BodyFactory.h"

#define MTP 30
#define PTM 1/30.0f

BodyFactory::BodyFactory(void) {}

BodyFactory::~BodyFactory(void) {}

void BodyFactory::createBox(b2Vec2 position, b2Vec2 size, b2World *world)
{
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
    myBodyDef.position.Set(position.x * PTM, position.y * PTM); //set the starting position
    myBodyDef.angle = 0; //set the starting angle
    
    b2Body* dynamicBody = world->CreateBody(&myBodyDef);
    
    b2PolygonShape boxShape;
    boxShape.SetAsBox(size.x * PTM, size.y * PTM);
    
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.restitution = 0;
    boxFixtureDef.friction = 1;
    dynamicBody->CreateFixture(&boxFixtureDef);
    
    world->CreateBody(&myBodyDef);
}

void BodyFactory::createFloor(b2Vec2 position, b2Vec2 size, b2World *world)
{
    b2BodyDef myBodyDef;
    myBodyDef.type = b2BodyType::b2_staticBody; //this will be a dynamic body
    myBodyDef.position.Set(position.x * PTM, position.y * PTM); //set the starting position
    myBodyDef.angle = 0; //set the starting angle
    b2Body* floorBody = world->CreateBody(&myBodyDef);
    
    b2PolygonShape boxShape;
    boxShape.SetAsBox(size.x * PTM, size.y * PTM);
    
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.restitution = 0;
    boxFixtureDef.friction = 1;
    
    floorBody->CreateFixture(&boxFixtureDef);
    
    b2BodyDef bodyDef;
    world->CreateBody(&bodyDef);
}
