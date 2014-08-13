#include "cocos2d.h"
#include <cmath>
#include <iostream>

#define RAD(angle) angle * M_PI / 180

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

    // is being existed?
    bool isDead = false;

    // can be crashed with other?
    bool canCrash = false;

    // current position, velocity, acceleration
    cocos2d::Vec2 position, velocity, accel;

    // basic status
    float angle = 0.f, speed = 0.f;
    

};