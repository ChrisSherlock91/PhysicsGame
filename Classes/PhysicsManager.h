//
//  PhysicsManager.h
//  PhysicsGame
//
//  Created by Chris Sherlock on 28/07/2016.
//
//

#ifndef PhysicsManager_h
#define PhysicsManager_h

#include <stdio.h>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "AppUtils.h"

using namespace cocos2d;

class PhysicsManager
{
public:
    PhysicsManager();
    ~PhysicsManager();
    
    static PhysicsManager* getInstance();
    static void releaseInstance();
    
    void update(float dt);
    
    void checkForClearLevel();
    void resetLevel();
    
    void drawLine(std::vector<std::pair<Vec2, Vec2>> points);

    b2Body* createStaticBody(Vec2 position, Vec2 size);
    void destroyBody(b2Body* body);
    
    b2Body* createBall(Vec2 position);
    
    // Getters
    b2World* getWorld() { return m_world; };
    
private:
    
    bool m_shouldClearLevel;
    
    b2World *m_world;
    
    std::vector<b2Body*> m_lineBodies;
    
    static PhysicsManager* ms_pInstance;
};

#endif /* PhysicsManager_h */
