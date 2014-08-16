#include "SkillUpgradeScene.h"
#include "HelloWorldScene.h"
using namespace cocos2d;

Scene* SkillUpgradeScene::createScene(){
	auto scene = Scene::create();

	auto layer = SkillUpgradeScene::create();

	scene->addChild(layer);
	
	return scene;

}

bool SkillUpgradeScene::init(){
	auto reducePollution = MenuItemFont::create("Reduce Pollution", CC_CALLBACK_1(SkillUpgradeScene::increasePollution, this));
	reducePollution->setColor(Color3B::MAGENTA);

	auto returnToMainScene = MenuItemFont::create("Return to aquarium", CC_CALLBACK_1(SkillUpgradeScene::returnToAquarium, this));
	auto menu = Menu::create(reducePollution, returnToMainScene, NULL);
	menu->alignItemsVertically();
	menu->setPosition(Point(700, 400));
	this->addChild(menu);

	return true;
}

void SkillUpgradeScene::increasePollution(Ref* pSender){

}

void SkillUpgradeScene::returnToAquarium(Ref* pSender){
	Director::getInstance()->popScene();
}

