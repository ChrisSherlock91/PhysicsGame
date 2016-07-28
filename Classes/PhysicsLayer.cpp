//
//  PhysicsLayer.cpp
//  PhysicsGame
//
//  Created by Chris Sherlock on 29/06/2016.
//
//

#include "PhysicsLayer.h"
#include "PhysicsManager.h"

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
    setDebugDraw(true);
    return true;
}

void PhysicsLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
    cocos2d::Layer::draw(renderer, transform, flags);
    
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    PhysicsManager::getInstance()->getWorld()->DrawDebugData();
    
    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void PhysicsLayer::update(float delta)
{
    PhysicsManager::getInstance()->update(delta);
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
        PhysicsManager::getInstance()->getWorld()->SetDebugDraw(debugDraw);
        PhysicsManager::getInstance()->getWorld()->DrawDebugData();
    }
    else
    {
        auto debugDraw = new GLESDebugDraw(32);
        debugDraw->SetFlags(0);
        PhysicsManager::getInstance()->getWorld()->SetDebugDraw(debugDraw);
    }
}

