#include "Area.h"

USING_NS_CC;

<<<<<<< HEAD
float Area::humanCoin, Area::ppm = 0.f, Area::stamina = 100.f, Area::amidTime = 0.f, Area::plaResSpeed = 0.5f;
int Area::maxPlanaria = 20, Area::deadPlas = 0, Area::cutPlas = 0;
=======
float Area::humanCoin, Area::ppm = 0.f, Area::stamina = 100.f, Area::amidTime = 0.f;
int Area::maxPlanaria = 20, Area::addedPlanaria[] = { 0 };
>>>>>>> f3452533c050d43f53bb9736818cccd513ab7980
LabelTTF *Area::coinLabel;
bool Area::isAmid = false;
bool Area::isNewPlanaria = false;
