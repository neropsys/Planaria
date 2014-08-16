#ifndef __SkillUpgrade_Scene__
#define __SkillUpgrade_Scene__
#include "cocos2d.h"

using namespace cocos2d;
class SkillUpgradeScene :public Layer
{
public:
	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(SkillUpgradeScene);
	void returnToAquarium(Ref* pSender);
	void increasePollution(Ref* pSender);
};


#endif