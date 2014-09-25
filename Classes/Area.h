#include "cocos2d.h"
#include "UnitBase.h"

#pragma once

class Area : public cocos2d::Layer {
public:
    static float humanCoin, ppm, stamina, amidTime;
    static cocos2d::LabelTTF *coinLabel;
	static int maxPlanaria, deadPlas, cutPlas;
    static bool isAmid;
    static float plaResSpeed;
	static int addedPlanaria[3];//index 0 : number of new extended planarias to be added
	static bool isNewPlanaria;//index 1 : number of new normal planarias to be added
protected:						//index 2 : number of new rainbow planarias to 
};