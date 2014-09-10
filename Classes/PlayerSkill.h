#include "UI.h"
#include "cocos2d.h"
#include "Planaria.h"
#include "Area.h"

class roseKnife : public SkillSlot {
public:
    CREATE_FUNC5(roseKnife);

protected:
    static cocos2d::Texture2D *starGraphic;
    cocos2d::Vector<cocos2d::ParticleFlower *> parts;

    cocos2d::Vec2 lastPoint;

    virtual void Init();

    virtual void activeSkill();

    virtual void Render();
};

class scoopPot : public SkillSlot {
public:
    CREATE_FUNC5(scoopPot);
protected:

    virtual void Init();

    virtual void activeSkill();
    virtual void Render();
};