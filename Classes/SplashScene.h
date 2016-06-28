//
//  SplashScene.h
//  PhysicsGame
//
//  Created by Chris Sherlock on 27/06/2016.
//
//

#ifndef SplashScene_h
#define SplashScene_h

#include <stdio.h>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"
USING_NS_CC;

using namespace cocos2d;

class SplashScene : public cocos2d::CCLayer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    virtual void update(float delta);
    
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);
    
    void createBox(Vec2 position);
    
    b2World *world;
    b2Body* m_groundBody;
    b2MouseJoint* m_mouseJoint;

    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);
};

#endif /* SplashScene_h */
