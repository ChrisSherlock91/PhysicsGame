//
//  MainScene.h
//  PhysicsGame
//
//  Created by Chris Sherlock on 28/06/2016.
//
//

#ifndef MainScene_h
#define MainScene_h

#include <stdio.h>
#include "cocos2d.h"
#include "PhysicsLayer.h"
#include "Ball.h"
#include "Target.h"

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    virtual void onExit();
    
    Vec2 m_touchPoint;
    
    DrawNode *m_drawNode;
    
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    
    void resetLevel(cocos2d::Ref *pSender);
    void startLevel(cocos2d::Ref *pSender);
    
    bool touchInsideNoDrawZone(Vec2 touchPoint);
    
    float getDistance(Vec2 pointOne, Vec2 pointTwo);
    
    std::vector<std::pair<Vec2, Vec2>> m_touchPositions;
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
private:
    PhysicsLayer* m_physicsLayer;
    Size m_visibleSize;
    Vec2 m_bombPosition;
    
    LayerColor* m_noDrawZone;
    
    Ball* m_ball;
    Target* m_target;
};


#endif /* MainScene_h */
