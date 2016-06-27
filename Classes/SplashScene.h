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

using namespace cocos2d;

class SplashScene : public cocos2d::CCLayer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);
};

#endif /* SplashScene_h */
