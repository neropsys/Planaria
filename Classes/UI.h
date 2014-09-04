#include "cocos2d.h"
#include "UnitBase.h"
#include "Mouse.h"
#pragma once

#define UI_FONT "Segoe UI"
#define SCRIPT_FONT "Comic Sans MS"
#define TITLE_FONT "Segoe UI"

// z-index layer
#define Z_UI 100
#define Z_UNIT 10
#define Z_BACK 0

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
    virtual void Init(const string &iconName);
    virtual void Run();
    virtual void Dead();

    virtual void activeSkill();
    virtual void passiveSkill();

    virtual void Render();

    bool actState = false;

    float coolTime = 0.f;

    float btnRadius = 24.f;

    string skillName;

    cocos2d::Director *oDir;
    cocos2d::LabelTTF *skillLabel;
    cocos2d::SpriteBatchNode *skillDisp;
    cocos2d::Sprite *skillBorder, *skillIcon;
    cocos2d::Color3B dispColor;

    RadioGroup *radioGroup;
};

class AreaUI : public UnitBase {
public:
	CREATE_FUNC3(AreaUI);
protected:
	virtual void Init();

	cocos2d::SpriteBatchNode *areaDisp;
	cocos2d::Sprite *borderLeft, *borderRight, *borderTop, *borderBottom;

	RadioGroup *skillGroup;
	SlotGroup *navGroup;
	SlotGroup *statGroup;
};
class UtilityButton : public UnitBase{
public:
	UtilityButton();
	virtual ~UtilityButton();
	virtual void create();
	//additional method may be added in the future
protected:
	virtual void gotoScene(cocos2d::Ref* pSender);

};

class Icon : public cocos2d::Node{
public:
	Icon();
	~Icon();
	void create(const std::string& outerName, const std::string& innerName, cocos2d::SpriteBatchNode** batch);
	cocos2d::Vec2 locationForLogo();
private:
	cocos2d::Sprite* outerSymbol;
	cocos2d::Sprite* innerSymbol;
	cocos2d::LabelTTF* iconLogo;
	float logoSize;
};