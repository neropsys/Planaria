#include "cocos2d.h"
#include "UnitBase.h"
#include "Mouse.h"

class SlotGroup : public UnitBase {
public:
    SlotGroup();
    ~SlotGroup();

    CREATE_FUNC(SlotGroup);

    void alignItems();

    float margin = 10.f;
protected:
};

class RadioGroup :public SlotGroup {
public:
    //static RadioSlot *create();
    CREATE_FUNC2(RadioGroup);

    virtual void addChild(cocos2d::Node *child);

    void ShareCoolTime();
protected:
};

class SkillSlot : public UnitBase {
public:
    SkillSlot();
    virtual ~SkillSlot();

    static SkillSlot *create();

    void turnOn();
    void turnOff();

    bool isActivated();

    void setCoolTime(float);

    virtual float getSize();

    void setGroup(RadioGroup *);
    RadioGroup *getGroup();

protected:
    virtual void Init();
    virtual void Run();
    virtual void Dead();

    virtual void activeSkill();
    virtual void passiaveSkill();

    virtual void Render();

    bool actState = false;

    float coolTime = 0.f;

    float btnRadius = 40.f;

    cocos2d::Director *oDir;

    cocos2d::DrawNode *btnModel;

    RadioGroup *radioGroup;
};

class UtilityButton : public UnitBase{
public:
	UtilityButton();
	virtual ~UtilityButton();
	virtual void create();
protected:
	virtual void gotoScene(cocos2d::Ref* pSender);
};