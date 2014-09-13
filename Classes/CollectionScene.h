#include "cocos2d.h"
#include "UI.h"
#pragma once
class CollectionScene : public cocos2d::Layer{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	virtual void onEnter();
	virtual void onExit();

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	CREATE_FUNC(CollectionScene);

	void Mainloop(float);

private:
	cocos2d::Sprite* b2Aquarium;
};