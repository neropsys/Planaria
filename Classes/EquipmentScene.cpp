#include "EquipmentScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;
Scene* EquipmentScene::createScene(){
	auto scene = Scene::create();
	auto layer = EquipmentScene::create();
	scene->addChild(layer);
	return scene;
}
bool EquipmentScene::init(){
	if (!Layer::init()){
		return false;
	}
	return true;
}
bool EquipmentScene::onTouchBegan(Touch* touch, Event* event){
	Mouse::onTouchBegan(touch, event);
	return true;
}
void EquipmentScene::onEnter(){
	Layer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(EquipmentScene::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto mouseBinder = EventListenerMouse::create();
}
void EquipmentScene::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}
