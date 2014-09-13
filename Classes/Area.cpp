#include "Area.h"

USING_NS_CC;

float Area::humanCoin, Area::ppm = 0.f, Area::stamina = 100.f, Area::amidTime = 0.f;
LabelTTF *Area::coinLabel;

bool Area::isAmid = false;