#include "cocos2d.h"
#pragma once

#define ADD_RETURN_BUTTON()\
	b2Aquarium = Sprite::create("b2aquarium.png");\
	b2Aquarium->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);\
	b2Aquarium->setPosition(visibleSize.width / 2, 0);\
	this->addChild(b2Aquarium);\

