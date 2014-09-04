#include "cocos2d.h"
#pragma once

#define ADD_RETURN_BUTTON()\
	b2Aquarium = Sprite::create("b2aquarium.png");\
	b2Aquarium->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);\
	b2Aquarium->setPosition(visibleSize.width / 2, 0);\
	this->addChild(b2Aquarium);
#define INIT_LISTENER(__SCENE_NAME__)\
	Layer::onEnter();\
	auto listener = EventListenerTouchOneByOne::create();\
	listener->setSwallowTouches(true);\
	listener->onTouchBegan = CC_CALLBACK_2(__SCENE_NAME__::onTouchBegan, this);\
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);\
	auto mouseBinder = EventListenerMouse::create();
#define INIT_SCENE(__SCENE_NAME__)\
	auto scene = Scene::create();\
	auto layer = __SCENE_NAME__::create();\
	scene->addChild(layer);\
	return scene;

//Additional function used on tech tree skill scenes may be added here in the future
