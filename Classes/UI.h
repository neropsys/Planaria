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

// Bend Funcs
#define GL_BLEND_BLENDMODE { GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA }
#define GL_BLEND_MULTIFLYMODE { GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA }
#define GL_BLEND_SCREENMODE { GL_ONE_MINUS_DST_COLOR, GL_ONE }
#define GL_BLEND_LINEARDODGEMODE { GL_ONE, GL_ONE }

#define CREATE_FUNC4(__TYPE_NAME__)\
static __TYPE_NAME__ *create(){\
	auto unit = new __TYPE_NAME__();\
	if (unit)\
		unit->autorelease();\
	else\
		CC_SAFE_DELETE(unit);\
	UIBase::UIQueue.pushBack(unit);\
	return unit;\
};
#define CREATE_FUNC5(__TYPE_NAME__)\
 __TYPE_NAME__() {};\
 ~__TYPE_NAME__() {};\
 static __TYPE_NAME__ *create(){\
	auto unit = new __TYPE_NAME__();\
	if (unit)\
		unit->autorelease();\
	else\
		CC_SAFE_DELETE(unit);\
	UIBase::UIQueue.pushBack(unit);\
	return unit;\
};

class UIBase : public cocos2d::Node {
public:
    UIBase();

    static void Initialize(cocos2d::Layer *layer);
    static void Mainloop();

    static cocos2d::Layer getLayer();

    cocos2d::Size &getBoxModel();
    cocos2d::Size &setBoxModel(const cocos2d::Size &size);

protected:
    static cocos2d::Vector<UIBase *> UIQueue, UICont, UIDead;

    static cocos2d::Layer *layer;

    virtual void Init();
    virtual void Render();
    virtual void Run();
    virtual void Dead();
    virtual void Click();
    virtual void Drag();

    cocos2d::Size boxModel;
};
class SlotGroup : public UIBase {
public:
    CREATE_FUNC5(SlotGroup);

    void alignItems();

    cocos2d::Vec2 &getNextPosition();

    virtual void addChildWithAction(cocos2d::Node *child);
protected:

    float margin = 10.f;
};

class RadioGroup : public SlotGroup {
public:
    CREATE_FUNC5(RadioGroup);

    virtual void addChild(cocos2d::Node *child);

    void ShareCoolTime();
protected:
};

class SkillSlot : public UIBase {
public:
    SkillSlot();
    ~SkillSlot();

    CREATE_FUNC4(SkillSlot);

    void turnOn();
    void turnOff();

    bool isActivated();

    void setCoolTime(float);

    void setGroup(RadioGroup *);
    RadioGroup *getGroup();

protected:
    virtual void Init(const string &iconName);
    virtual void Run();
    virtual void Dead();
    virtual void Click();
    virtual void Render();

    virtual void activeSkill();
    virtual void passiveSkill();

    bool actState = false;

    float coolTime = 0.f;

    string skillName;

    cocos2d::Director *oDir;
    cocos2d::LabelTTF *skillLabel;
    cocos2d::SpriteBatchNode *skillDisp;
    cocos2d::Sprite *skillBorder, *skillIcon;
    cocos2d::Color3B dispColor;

    RadioGroup *radioGroup;
};

class AreaUI : public UIBase {
public:
	AreaUI();
	virtual ~AreaUI();
	CREATE_FUNC4(AreaUI);
	RadioGroup *getSkillGroup();
	SlotGroup *getNavGroup();
	SlotGroup *getStatGroup();
protected:
	virtual void Init();
	virtual void Dead();
	virtual void Run();

	cocos2d::SpriteBatchNode *areaDisp;
	cocos2d::Sprite *borderLeft, *borderRight, *borderTop, *borderBottom;

	RadioGroup* skillGroup;
	SlotGroup* navGroup;
	SlotGroup* statGroup;
};

class Profile : public UIBase{
public:
	Profile();
	~Profile();

	CREATE_FUNC4(Profile);

	static Profile *create(const string &profileImage);

    cocos2d::LabelTTF *getLabel() { return profileText; }
    cocos2d::LabelTTF *getName() { return profileName; }
    cocos2d::Sprite *getProfileCircle() { return profileCircle; }
	cocos2d::Sprite *getProfileImg() { return profileImg; }

	void setProfileImgRate(float rate);
	float getProfileImgRate() { return profileImgRate; }

protected:

	virtual void Init();
	virtual void Render();

	cocos2d::SpriteBatchNode *profileDisp;
	cocos2d::Sprite *profileCircle, *profileImg;

	cocos2d::LabelTTF *profileText, *profileName;

	cocos2d::Size originalSize;

	float profileImgRate = 1.0f;

	string profileImgName;
};

class UtilityButton : public UIBase{
public:
	UtilityButton();
	virtual ~UtilityButton();
	virtual void create();
	//additional method may be added in the future
protected:
	virtual void gotoScene(cocos2d::Ref* pSender);
    virtual void Init();
    virtual void Dead();
	virtual void Run();
};