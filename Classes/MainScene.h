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

class MainScene : public cocos2d::Layer
{
private:
    PhysicsLayer* m_physicsLayer;
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
};


#endif /* MainScene_h */
