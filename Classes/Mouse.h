#include "cocos2d.h"

#pragma once

class Mouse {
public:
    static cocos2d::Vec2 &getPoint();
    static bool isDown();

    static float getSize();

    static int getTouchID();

    static bool isFirst();
    
    static bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    static void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    static void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    static void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

    static void Initialize();

protected:
    static cocos2d::Vec2 point;

    static bool isTouching;
    static bool isStart;
    static int touchID;

    static float cursorSize;
};