#include "cocos2d.h"
#include "UnitBase.h"

#pragma once

class Area : public cocos2d::Layer {
public:
    static float humanCoin, ppm, stamina, amidTime;
    static cocos2d::LabelTTF *coinLabel;
	static int maxPlanaria;
    static bool isAmid;

protected:
};