#include "UI.h"
#include "cocos2d.h"
#include "Planaria.h"
#include "Area.h"
#define DECONTAMINANT_VALUE 10
#define ST_DECREASE_RATE .85f
class RoseKnife : public SkillSlot {
public:
    CREATE_FUNC5(RoseKnife);


protected:
    static cocos2d::Texture2D *starGraphic;
    cocos2d::Vector<cocos2d::ParticleFlower *> parts;

    cocos2d::Vec2 lastPoint;

	float decreaseRate;

    virtual void Init();

    virtual void activeSkill();

    virtual void Render();
};
class Decontaminant : public SkillSlot{
public:
	CREATE_FUNC5(Decontaminant);
protected:
	virtual void Init();

	virtual void activeSkill();
	virtual void Render();
};
class ScoopPot : public SkillSlot {
public:
    CREATE_FUNC5(ScoopPot);
protected:

    virtual void Init();

    virtual void activeSkill();
    virtual void Render();
};
class SkillSceneBtn : public UtilityButton{
public:
	SkillSceneBtn();
	~SkillSceneBtn();
	void gotoScene();
private:
	cocos2d::Sprite* skillButtonSprite;
};
class ShopButton : public UtilityButton{
public:
	ShopButton();
	~ShopButton();
	void gotoScene();
private:
	cocos2d::Sprite* shopButtonSprite;
};