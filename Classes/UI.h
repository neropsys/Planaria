#include "cocos2d.h"
#include "UnitBase.h"
#include "Mouse.h"

class ItemSlot : public UnitBase {
public:
    ItemSlot();
    ~ItemSlot();

    CREATE_FUNC(ItemSlot);

    void alignItems();

    float margin = 10.f;
protected:
};

class RadioSlot :public ItemSlot {
public:
    //static RadioSlot *create();
    CREATE_FUNC2(RadioSlot);

    virtual void addChild(cocos2d::Node *child);

    void ShareCoolTime();
protected:
};

class QuickSlot : public UnitBase {
public:
    QuickSlot();
    virtual ~QuickSlot();

    static QuickSlot *create();

    void turnOn();
    void turnOff();

    bool isActivated();

    void setCoolTime(float);

    virtual float getSize();

    void setGroup(RadioSlot *);
    RadioSlot *getGroup();

protected:
    virtual void Init();
    virtual void Run();
    virtual void Dead();

    virtual void activeSkill();
    virtual void passiaveSkill();

    virtual void Render();

    bool actState = false;

    float coolTime = 0.f;

    float btnRadius = 32.f;

    cocos2d::Director *oDir;

    cocos2d::DrawNode *btnModel;

    RadioSlot *radioGroup;
};