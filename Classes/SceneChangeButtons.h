#include "cocos2d.h"
#pragma once
class MenuButton{
public:
	cocos2d::Menu* create(float width, float height);
	MenuButton();
	~MenuButton();
private:
	cocos2d::MenuItemImage* collectionScene;
	cocos2d::MenuItemImage* constructionScene;
	cocos2d::MenuItemImage* valueScene;
	cocos2d::MenuItemImage* equipmentScene;
	void collectionSceneCallback(cocos2d::Ref* pSender);
	void constructionSceneCallback(cocos2d::Ref* pSender);
	void valueSceneCallback(cocos2d::Ref* pSender);
	void equipmentSceneCallback(cocos2d::Ref* pSender);

};