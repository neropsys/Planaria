#include "Area.h"

USING_NS_CC;

float Area::humanCoin, Area::ppm = 0.f, Area::stamina = 100.f, Area::amidTime = 0.f;
int Area::maxPlanaria = 20;
LabelTTF *Area::coinLabel;

bool Area::isAmid = false;