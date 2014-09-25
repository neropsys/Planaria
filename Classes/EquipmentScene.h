#include "cocos2d.h"
#pragma once
class EquipmentScene : public cocos2d::Layer{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	virtual void onEnter();
	virtual void onExit();

    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);

	CREATE_FUNC(EquipmentScene);
private:
	cocos2d::Sprite* b2Aquarium;
};