#include "cocos2d.h"
#pragma once

using namespace cocos2d;
class SkillUpgradeScene :public Layer
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

	void returnToAquarium(Ref* pSender);
private:
	Sprite* b2Aquarium;
};
