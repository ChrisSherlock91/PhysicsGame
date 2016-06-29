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
USING_NS_CC;

class PhysicsLayer : public cocos2d::Layer
{
private:
    void setDebugDraw(bool set);
    
public:
    static PhysicsLayer* createLayer();
    
    virtual bool init();
    virtual void update(float delta);
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);
    
    void createBox(b2Vec2 position, b2Vec2 size);
    void createFloor(b2Vec2 position, b2Vec2 size);
    void createArrow(b2Vec2 position);

 
    b2World *m_world;
   
    // implement the "static create()" method manually
    CREATE_FUNC(PhysicsLayer);
};


#endif /* PhysicsLayer_h */
