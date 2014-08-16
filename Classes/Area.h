#include "cocos2d.h"
#include "UnitBase.h"

#pragma once

class Area : public UnitBase {
public:
    static float humanCoin;
    static cocos2d::LabelTTF *coinLabel;
	static float pollutionRate;
	static cocos2d::LabelTTF* pollutionLabel;

protected:
};