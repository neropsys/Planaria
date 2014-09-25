#include "SceneChangeButtons.h"
#include "CollectionScene.h"
#include "EquipmentScene.h"
#include "ConstructionScene.h"
#include "ValueScene.h"
USING_NS_CC;
#define POP_AND_PUSH(__SCENE_NAME__)\
	auto newScene = __SCENE_NAME__::createScene();\
	Director::getInstance()->popScene();\
	Director::getInstance()->pushScene(newScene);
MenuButton::MenuButton():
	collectionScene (MenuItemImage::create("scenebutton/collectionSceneButton.png",
		"scenebutton/collectionSceneSelected.png",CC_CALLBACK_1(MenuButton::collectionSceneCallback, this))),
	constructionScene (MenuItemImage::create("scenebutton/collectionSceneButton.png",
		"scenebutton/collectionSceneSelected.png", CC_CALLBACK_1(MenuButton::collectionSceneCallback, this))),
	valueScene (MenuItemImage::create("scenebutton/valueSceneButton.png",
		"scenebutton/valueSceneSelected.png", CC_CALLBACK_1(MenuButton::valueSceneCallback, this))),
	equipmentScene (MenuItemImage::create("scenebutton/equipmentSceneButton.png",
		"scenebutton/equipmentSceneSelected.png",CC_CALLBACK_1(MenuButton::equipmentSceneCallback, this))){
}
MenuButton::~MenuButton(){}

void MenuButton::collectionSceneCallback(cocos2d::Ref* pSender){
	POP_AND_PUSH(CollectionScene);
}
void MenuButton::constructionSceneCallback(cocos2d::Ref* pSender){
	POP_AND_PUSH(ConstructionScene);
}
void MenuButton::equipmentSceneCallback(cocos2d::Ref* pSender){
	POP_AND_PUSH(EquipmentScene);
}
void MenuButton::valueSceneCallback(cocos2d::Ref* pSender){
	POP_AND_PUSH(ValueScene);
}


Menu* MenuButton::create(float width, float height){
	auto menuList = Menu::create(collectionScene, constructionScene, equipmentScene, valueScene, NULL);
	menuList->alignItemsHorizontally();
	menuList->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	menuList->setPosition(width, height);
	return menuList;
}