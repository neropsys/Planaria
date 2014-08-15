#include "cocos2d.h"
#include "UnitBase.h"
#include "Mouse.h"

class QuickSlot : public UnitBase {
public:
    QuickSlot();
    virtual ~QuickSlot();

    static QuickSlot *create();

    void turnOn();
    void turnOff();

    bool isActivated();

    void setCoolTime();

protected:
    virtual void Init();
    virtual void Run();
    virtual void Dead();

    virtual void skillSet();

    virtual void Render();

    bool actState = false;

    float coolTime = 0.f;

    float btnRadius = 32.f;

    cocos2d::Director *oDir;

    cocos2d::DrawNode *btnModel;
};