//
//  PhysicsLayer.h
//  PhysicsGame
//
//  Created by Chris Sherlock on 29/06/2016.
//
//

#ifndef PhysicsLayer_h
#define PhysicsLayer_h

#include <stdio.h>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"
#include "ContactListener.h"
USING_NS_CC;

class PhysicsLayer : public cocos2d::Layer
{
private:
    void setDebugDraw(bool set);
    
    Vec2 m_origin;
    b2Body* m_bomb;
    bool m_shouldClearLevel;
    std::vector<b2Body*> m_lineBodies;
    
    ContactListener* m_contactListener;
    
public:
    static PhysicsLayer* createLayer();
    
    virtual bool init();
    virtual void update(float delta);
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);

    void resetLevel();
    void checkForClearLevel();
    
    void createBox(b2Vec2 position, b2Vec2 size, ContactListener::EntityType type);
    void createFloor(b2Vec2 position, b2Vec2 size);
    void setBombActive();
    void createBomb(b2Vec2 position);
    void createTarget(b2Vec2 position);
    
    void drawLine(std::vector<std::pair<Vec2, Vec2>> points);
    
    
    b2Body *dynamicBody;
    b2Body *m_floorBody;
 
    b2World *m_world;
   
    // implement the "static create()" method manually
    CREATE_FUNC(PhysicsLayer);
};


#endif /* PhysicsLayer_h */
