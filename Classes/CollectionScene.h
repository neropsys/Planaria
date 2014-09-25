#include "cocos2d.h"
#include "UI.h"
#include "TechTreeSceneTemplate.h"
#include "Area.h"
#include "Planaria.h"
#include "SceneChangeButtons.h"
#pragma once
#define MAXNUMBER 40
#define EXT_AQUARIUM_VALUE 100
#define PLATONIC_VALUE 100
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
	cocos2d::Sprite* nova;
	cocos2d::Sprite* fishTank;
	cocos2d::Sprite* roseKnife;
	cocos2d::Sprite* platonic;
	cocos2d::Size visibleSize;
};