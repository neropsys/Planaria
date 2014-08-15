#include "UI.h"
#include "cocos2d.h"
#include "Planaria.h"

class roseKnife : public QuickSlot {
public:
    roseKnife();
    ~roseKnife();

    static roseKnife *create();
protected:
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