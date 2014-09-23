#include "cocos2d.h"
#include "Area.h"
#pragma once

class ShopScene : public cocos2d::Layer{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	virtual void onEnter();
	virtual void onExit();

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	CREATE_FUNC(ShopScene);

private:
	cocos2d::Size visibleSize;
	cocos2d::Sprite* b2Aquarium;
	cocos2d::Sprite* planariaButton;
};