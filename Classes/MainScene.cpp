//
//  MainScene.cpp
//  PhysicsGame
//
//  Created by Chris Sherlock on 28/06/2016.
//
//

#include "MainScene.h"

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    m_physicsLayer = PhysicsLayer::createLayer();
    this->addChild(m_physicsLayer);
    
    
    m_physicsLayer->createFloor(b2Vec2(0, visibleSize.height * 0.1), b2Vec2(visibleSize.width, visibleSize.height * 0.1));
    m_physicsLayer->createBox(b2Vec2(visibleSize.width / 2, visibleSize.height / 2), b2Vec2(10,10));
    m_physicsLayer->createArrow(b2Vec2(visibleSize.width * 0.1, visibleSize.height * 0.15));
    
    
    
    return true;
}