#include "cocos2d.h"
#include <cmath>
#include <iostream>

#pragma once

#define RAD(angle) angle * M_PI / 180

// this is inline function to realize static create* method
#define CREATE_FUNC2(__TYPE_NAME__) __TYPE_NAME__() {}; ~__TYPE_NAME__() {}; static __TYPE_NAME__ *create() { auto unit = new __TYPE_NAME__(); if (unit) { unit->autorelease(); } else { CC_SAFE_DELETE(unit); } UnitBase::newUnit.pushBack(unit); return unit; };
#define DELETE_OBJ(__OBJECT__) if ( __OBJECT__ ) { __OBJECT__->release(); __OBJECT__ = NULL; }

using namespace std;

// the root of unit class
class UnitBase : public cocos2d::Node {
public:
    UnitBase();
    ~UnitBase();

    // basic bone
    static UnitBase *create();
    
    // when initialize, main frame, finalize
    static void Initialize(cocos2d::Layer*);
    static void Mainloop();
    static void Finalize();

    // event 
    static bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    static void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    static void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    static void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

    // base
    virtual void setAngle(float angle);
    virtual float getAngle();

    virtual void setSpeed(float speed);
    virtual float getSpeed();

    virtual void setSize(float size);
    virtual float getSize();

    virtual void setPosition(float x, float y);
    virtual cocos2d::Vec2 &getPosition();

    virtual void setMove(float angle, float speed);
    virtual void setMove(const cocos2d::Vec2&);

    virtual bool isCrash(const cocos2d::Vec2& point, float radius);
    virtual bool isCrash(float x, float y, float radius);

    void Die();

protected:
    // for managing unit objects.
    static cocos2d::Vector<UnitBase *> newUnit;
    static cocos2d::Vector<UnitBase *> crtUnit;
    static cocos2d::Vector<UnitBase *> deadUnit;

    // crt layer
    static cocos2d::Layer *layer;

    // when unit is created, being existed, crashed with other thing, dead and destroyed.
    virtual void Init();
    virtual void Run();
    virtual void Coll(UnitBase *);
    virtual void Dead();
    virtual void Final();

    // calculate velocity from angle and speed of itself
    void setVelocity();

    // is being existed?
    bool isDead = false;

    // can be crashed with other?
    bool canCrash = false;

    // current position, velocity, acceleration
    cocos2d::Vec2 position, velocity;

    // basic status
    float angle = 0.f, speed = 0.f;
    float bodySize = 0.f;
};