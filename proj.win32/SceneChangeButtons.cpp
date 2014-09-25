#include "SceneChangeButtons.h"
#include "CollectionScene.h"
#include "EquipmentScene.h"
#include "ConstructionScene.h"
#include "ValueScene.h"
USING_NS_CC;
MenuButton::MenuButton() : collectionScene(MenuItemImage::create("scenebutton/collectionSceneButton.png",
	"scenebutton/collectionSceneSelected.png", MenuButton::collectionSceneCallback)), 
	constructionScene(MenuItemImage::create("scenebutton/collectionSceneButton.png",
	"scenebutton/collectionSceneSelected.png", MenuButton::collectionSceneCallback)),
	valueScene(MenuItemImage::create("", "", MenuButton::valueSceneCallback)),
	equipmentScene(MenuItemImage::create("", "", MenuButton::equipmentSceneCallback)){
}
MenuButton::~MenuButton(){}

void MenuButton::collectionSceneCallback(cocos2d::Ref* pSender){

}