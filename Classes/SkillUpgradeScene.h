#include "cocos2d.h"
#pragma once

using namespace cocos2d;
class SkillUpgradeScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SkillUpgradeScene);

	virtual void onEnter();
	virtual void onExit();

	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	virtual void onTouchCancelled(Touch* touch, Event* event);
private:
	Sprite* b2Aquarium;
	Color4F circleColor = Color4F::BLUE;
	float circleRadius = 120.f;
	Vec2 midPoint;
	DrawNode* middleCircle;
	LabelTTF* equipmentText;
	LabelTTF* constructText;
	LabelTTF* valueText;
	LabelTTF* collectionText;
};
