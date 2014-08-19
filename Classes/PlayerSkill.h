#include "UI.h"
#include "cocos2d.h"
#include "Planaria.h"

class roseKnife : public QuickSlot {
public:
    roseKnife();
    ~roseKnife();

    static roseKnife *create();

protected:
    static cocos2d::Texture2D *starGraphic;
    cocos2d::Vector<cocos2d::ParticleFlower *> parts;

    cocos2d::Vec2 lastPoint;

    virtual void Init();

    virtual void activeSkill();

    virtual void Render();

    int t = 0;
};

class scoopPot : public QuickSlot {
public:
    CREATE_FUNC2(scoopPot);
protected:

    virtual void activeSkill();
    virtual void Render();
};