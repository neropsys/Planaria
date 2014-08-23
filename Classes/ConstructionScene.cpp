#include "ConstructionScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;
Scene* ConstructionScene::createScene(){
	auto scene = Scene::create();
	auto layer = ConstructionScene::create();
	scene->addChild(layer);
	return scene;
}
bool ConstructionScene::init(){
	if (!Layer::init()){
		return false;
	}
	return true;
}
bool ConstructionScene::onTouchBegan(Touch* touch, Event* event){
	Mouse::onTouchBegan(touch, event);
	return true;
}
void ConstructionScene::onEnter(){
	Layer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ConstructionScene::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto mouseBinder = EventListenerMouse::create();
}
void ConstructionScene::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}
