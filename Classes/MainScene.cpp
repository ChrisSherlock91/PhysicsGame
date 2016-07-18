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
    m_visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    m_touchPoint = Vec2(0,0);
    
    m_physicsLayer = PhysicsLayer::createLayer();
    this->addChild(m_physicsLayer);
    
    
    m_physicsLayer->createFloor(b2Vec2(0, m_visibleSize.height * 0.1), b2Vec2(m_visibleSize.width, m_visibleSize.height * 0.1));

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(MainScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(MainScene::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(MainScene::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    MenuItemSprite *menu_item1 = MenuItemSprite::create(Sprite::create("PlayBtn.png"), Sprite::create("PlayBtn.png"), CC_CALLBACK_1(MainScene::startLevel, this));
    menu_item1->setPosition(Vec2(m_visibleSize.width * 0.95, m_visibleSize.height * 0.95));
    menu_item1->setAnchorPoint(Vec2(1, 0.5f));
    menu_item1->setScale(0.3f);
    
    auto *menu = Menu::create(menu_item1, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);
    
    m_drawNode = DrawNode::create();
    this->addChild(m_drawNode, 10);
    
    createBomb();
    
    return true;
}

void MainScene::startLevel(cocos2d::Ref *pSender)
{
    CCLOG("--- Test ---");
    m_physicsLayer->setBombActive();
}

void MainScene::createBomb()
{
    m_physicsLayer->createBomb(b2Vec2(m_visibleSize.width * 0.1, m_visibleSize.height * 0.9));
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

