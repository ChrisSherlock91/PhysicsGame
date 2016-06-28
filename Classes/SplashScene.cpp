//
//  SplashScene.cpp
//  PhysicsGame
//
//  Created by Chris Sherlock on 27/06/2016.
//
//
#include "SplashScene.h"

#define MTP 30
#define PTM 1/30.0f

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
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
    world = new b2World(gravity);
    
    b2BodyDef myBodyDef;
    myBodyDef.type = b2BodyType::b2_staticBody; //this will be a dynamic body
    myBodyDef.position.Set(visibleSize.width / 2 * PTM, (visibleSize.height * 0.1) * PTM); //set the starting position
    myBodyDef.angle = 0; //set the starting angle
    b2Body* dynamicBody = world->CreateBody(&myBodyDef);
    
    b2PolygonShape boxShape;
    boxShape.SetAsBox(visibleSize.width * PTM, (visibleSize.height * 0.01) * PTM);
    
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.restitution = 0;
    boxFixtureDef.friction = 1;
    
    dynamicBody->CreateFixture(&boxFixtureDef);
    
    b2BodyDef bodyDef;
    m_groundBody = world->CreateBody(&bodyDef);
    
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    flags += b2Draw::e_jointBit;
    flags += b2Draw::e_aabbBit;
    flags += b2Draw::e_pairBit;
    flags += b2Draw::e_centerOfMassBit;
    flags += b2Draw::e_aabbBit;
    auto debugDraw = new GLESDebugDraw(32);
    debugDraw->SetFlags(flags);
    world->SetDebugDraw(debugDraw);
    world->DrawDebugData();
    
    createBox(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    
    return true;
}

void SplashScene::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
    cocos2d::Layer::draw(renderer, transform, flags);
    
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    world->DrawDebugData();
    
    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void SplashScene::update(float delta)
{
    int velocityIterations = 8;
    int positionIterations = 3;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world->Step(delta, velocityIterations, positionIterations);
    
    // Iterate over the bodies in the physics world
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
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

void SplashScene::createBox(Vec2 position)
{
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
    myBodyDef.position.Set(position.x * PTM, position.y * PTM); //set the starting position
    myBodyDef.angle = 0; //set the starting angle
    
    b2Body* dynamicBody = world->CreateBody(&myBodyDef);
    
    b2PolygonShape boxShape;
    boxShape.SetAsBox(10 * PTM, 10 * PTM);
    
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.restitution = 0;
    boxFixtureDef.friction = 1;
    dynamicBody->CreateFixture(&boxFixtureDef);
    
    world->CreateBody(&myBodyDef);
}


