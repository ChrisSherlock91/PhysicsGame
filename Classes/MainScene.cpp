//
//  MainScene.cpp
//  PhysicsGame
//
//  Created by Chris Sherlock on 28/06/2016.
//
//

#include "MainScene.h"

#define DRAW_DISTANCE 40

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
    m_bombPosition = b2Vec2(m_visibleSize.width * 0.1f, m_visibleSize.height * 0.9);
    m_touchPoint = Vec2(0,0);
    
    m_physicsLayer = PhysicsLayer::createLayer();
    this->addChild(m_physicsLayer);
    
    
    m_physicsLayer->createFloor(b2Vec2(0, m_visibleSize.height * 0.1), b2Vec2(m_visibleSize.width, m_visibleSize.height * 0.1));
    m_physicsLayer->createTarget(b2Vec2(m_visibleSize.width * 0.9, m_visibleSize.height * 0.2));
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(MainScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(MainScene::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(MainScene::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    MenuItemSprite *playBtn = MenuItemSprite::create(Sprite::create("PlayBtn.png"), Sprite::create("PlayBtn.png"), CC_CALLBACK_1(MainScene::startLevel, this));
    playBtn->setPosition(Vec2(m_visibleSize.width * 0.95, m_visibleSize.height * 0.95));
    playBtn->setAnchorPoint(Vec2(1, 0.5f));
    playBtn->setScale(0.3f);
    
    MenuItemSprite *retryBtn = MenuItemSprite::create(Sprite::create("RetryBtn.png"), Sprite::create("RetryBtn.png"), CC_CALLBACK_1(MainScene::resetLevel, this));
    retryBtn->setPosition(Vec2(playBtn->getPositionX(), playBtn->getPositionY() - playBtn->getContentSize().height * 0.4f));
    retryBtn->setAnchorPoint(playBtn->getAnchorPoint());
    retryBtn->setScale(0.3f);
    
    auto *menu = Menu::create(playBtn, retryBtn, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);
    
    m_drawNode = DrawNode::create();
    this->addChild(m_drawNode, 10);
    
    m_noDrawZone = LayerColor::create(Color4B(255, 200, 200, 230));
    m_noDrawZone->setPosition(Vec2(m_visibleSize.width * 0.2, m_visibleSize.height * 0.5));
    m_noDrawZone->setContentSize(Size(100, 100));
    this->addChild(m_noDrawZone, 100);
    
    createBomb();
    
    return true;
}

void MainScene::startLevel(cocos2d::Ref *pSender)
{
    m_physicsLayer->setBombActive();
}

void MainScene::resetLevel(cocos2d::Ref *pSender)
{
    m_touchPositions.clear();
    m_physicsLayer->resetLevel();
    m_drawNode->clear();
    m_physicsLayer->createBomb(m_bombPosition);
}

void MainScene::createBomb()
{
    m_physicsLayer->createBomb(m_bombPosition);
}

// Check if we are trying to draw inside a no draw area
bool MainScene::touchInsideNoDrawZone(Vec2 touchPoint)
{
    float x = m_noDrawZone->getPosition().x;
    float y = m_noDrawZone->getPosition().y;
    float width = m_noDrawZone->getContentSize().width;
    float height = m_noDrawZone->getContentSize().height;
    
    if (touchPoint.x < (x + width) && touchPoint.x > x &&
        touchPoint.y < (y + height) && touchPoint.y > y)
        return true;
    else
        return false;
}

void MainScene::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {}

void MainScene::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    cocos2d::Touch *touch = (*touches.begin());
    if(!touchInsideNoDrawZone(touch->getLocation()))
    {
        if(getDistance(touch->getPreviousLocation(), touch->getLocation()) < DRAW_DISTANCE)
        {
            m_touchPositions.push_back(std::make_pair(touch->getPreviousLocation(), touch->getLocation()));
            m_drawNode->drawSegment(touch->getPreviousLocation(), touch->getLocation(), 2, Color4F::YELLOW);
        }
    }
}

float MainScene::getDistance(Vec2 pointOne, Vec2 pointTwo)
{
    float diffY = pointOne.y - pointTwo.y;
    float diffX = pointOne.x - pointTwo.x;
    return sqrt((diffY * diffY) + (diffX * diffX));
}

void MainScene::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    CCLOG("---- Touch Ended ----");
    m_physicsLayer->drawLine(m_touchPositions);
}

