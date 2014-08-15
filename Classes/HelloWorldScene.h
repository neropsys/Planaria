#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PlanariaUnits.h"
#include "PlayerSkill.h"

#define _WEAPON_ 100

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    virtual void onEnter();
    virtual void onExit();

    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void weaponMenuCallback(cocos2d::Ref *pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    void Mainloop(float);

    float getNext();

protected:

    int t = 0;

};

#endif // __HELLOWORLD_SCENE_H__
