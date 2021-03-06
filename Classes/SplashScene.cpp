//
//  SplashScene.cpp
//  PhysicsGame
//
//  Created by Chris Sherlock on 27/06/2016.
//
//
#include "SplashScene.h"

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    return true;
}


