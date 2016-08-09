//
//  MainScene.cpp
//  PhysicsGame
//
//  Created by Chris Sherlock on 28/06/2016.
//
//

#include "MainScene.h"
#include "PhysicsManager.h"

#define DRAW_DISTANCE 100

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

void MainScene::onExit()
{
    delete m_ball;
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
    m_bombPosition = Vec2(m_visibleSize.width * 0.1f, m_visibleSize.height * 0.9);
    m_touchPoint = Vec2(0,0);
    m_currentDistanceDrawn = 0;
    m_maxDrawAmount = 400;
    
    m_physicsLayer = PhysicsLayer::createLayer();
    this->addChild(m_physicsLayer);
   
    m_ball = new Ball(m_bombPosition);
    m_target = new Target(Vec2(m_visibleSize.width * 0.9, m_visibleSize.height * 0.3), Vec2(m_visibleSize.width * 0.03, m_visibleSize.height * 0.06));
    this->addChild(m_target);
    
    // Create Floor
    PhysicsManager::getInstance()->createStaticBody(Vec2(0, m_visibleSize.height * 0.2), Vec2(m_visibleSize.width, m_visibleSize.height * 0.02));
    
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
    m_noDrawZone->setContentSize(Size(200, 200));
    this->addChild(m_noDrawZone, 100);
    
    // Create the loading bar
    m_progressBar = cocos2d::ui::LoadingBar::create("sliderProgress.png");
    m_progressBar->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height * 0.99));
    m_progressBar->setDirection(cocos2d::ui::LoadingBar::Direction::LEFT);
    m_progressBar->setPercent(100);
    m_progressBar->setScale(2);
    this->addChild(m_progressBar);
    
    
//    auto map = TMXTiledMap::create("LevelOne.tmx");
//    this->addChild(map, 0);
    
    return true;
}

void MainScene::startLevel(cocos2d::Ref *pSender)
{
    m_ball->setActive();
}

void MainScene::resetLevel(cocos2d::Ref *pSender)
{
    m_currentDistanceDrawn = 0;
    m_progressBarWidth = m_visibleSize.width * 0.4;
    m_touchPositions.clear();
    PhysicsManager::getInstance()->resetLevel();
    m_drawNode->clear();
    m_ball->reset();
    m_progressBar->setPercent(100);
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
        float distance = getDistance(touch->getPreviousLocation(), touch->getLocation());
        m_currentDistanceDrawn += distance;
        float drawnPercent = (m_currentDistanceDrawn / m_maxDrawAmount);
        m_progressBar->setPercent(100 - (drawnPercent*100));
        
        if(distance < DRAW_DISTANCE && checkDrawAmount())
        {
            m_touchPositions.push_back(std::make_pair(touch->getPreviousLocation(), touch->getLocation()));
            m_drawNode->drawSegment(touch->getPreviousLocation(), touch->getLocation(), 4, Color4F::YELLOW);
        }
    }
}

float MainScene::getDistance(Vec2 pointOne, Vec2 pointTwo)
{
    float diffY = pointOne.y - pointTwo.y;
    float diffX = pointOne.x - pointTwo.x;
    return sqrt((diffY * diffY) + (diffX * diffX));
}

bool MainScene::checkDrawAmount()
{
    if(m_currentDistanceDrawn < m_maxDrawAmount)
        return true;
    return false;
}

void MainScene::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    PhysicsManager::getInstance()->drawLine(m_touchPositions);
}
