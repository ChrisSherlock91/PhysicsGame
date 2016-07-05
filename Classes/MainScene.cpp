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
    
    m_touchPoint = Vec2(0,0);
    
    m_physicsLayer = PhysicsLayer::createLayer();
    this->addChild(m_physicsLayer);
    
    
    m_physicsLayer->createFloor(b2Vec2(0, visibleSize.height * 0.1), b2Vec2(visibleSize.width, visibleSize.height * 0.1));

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(MainScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(MainScene::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(MainScene::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    m_drawNode = DrawNode::create();
    this->addChild(m_drawNode, 10);//Make sure your z-order is large enough
    
    return true;
}

void MainScene::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    log("---- Touch Began ----");
}

void MainScene::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    cocos2d::Touch *touch = (*touches.begin());
    m_touchPositions.push_back(std::make_pair(touch->getPreviousLocation(), touch->getLocation()));
    m_drawNode->drawSegment(touch->getPreviousLocation(), touch->getLocation(), 2, Color4F::YELLOW);
}

void MainScene::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    CCLOG("---- Touch Ended ----");
    m_physicsLayer->drawLine(m_touchPositions);
}

