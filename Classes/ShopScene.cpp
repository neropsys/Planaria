#include "ShopScene.h"
#include "HelloWorldScene.h"
#include "TechTreeSceneTemplate.h"
#define PLANARIA_VALUE 5
USING_NS_CC;
Scene* ShopScene::createScene(){
	INIT_SCENE(ShopScene);
}

bool ShopScene::init(){
	if (!Layer::init()) return false;
	visibleSize = Director::getInstance()->getVisibleSize();

	planariaButton = Sprite::create("planariabutton.png");
	this->addChild(planariaButton);

	ADD_RETURN_BUTTON();
	return true;
}
bool ShopScene::onTouchBegan(Touch* touch, Event* event){
	Mouse::onTouchBegan(touch, event);

	auto touchPt = touch->getLocation();
	auto bTouch = b2Aquarium->getBoundingBox().containsPoint(touchPt);//does not work with Mouse::getPoint
	if (bTouch){
		Director::getInstance()->popScene();
		return true;
	}
	if (planariaButton->getBoundingBox().containsPoint(touchPt)){
		if (Area::humanCoin < 5) return true;
		Area::humanCoin -= PLANARIA_VALUE;
		NormalPlanaria* pl = NormalPlanaria::create();
		pl->setMove(getNext() * 360, 0.5);
		pl->setPosition(visibleSize.width*getNext(), visibleSize.height*getNext());
	}
	return true;
}
void ShopScene::onEnter(){
	INIT_LISTENER(ShopScene);
}
void ShopScene::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Mouse::Initialize();

	Layer::onExit();
}

float HelloWorld::getNext() {
	return (float)rand() / RAND_MAX;
}