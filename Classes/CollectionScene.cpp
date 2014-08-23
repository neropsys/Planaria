#include "CollectionScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;
Scene* CollectionScene::createScene(){
	auto scene = Scene::create();
	auto layer = CollectionScene::create();
	scene->addChild(layer);
	return scene;
}
bool CollectionScene::init(){
	if (!Layer::init()){
		return false;
	}
	return true;
}
bool CollectionScene::onTouchBegan(Touch* touch, Event* event){
	Mouse::onTouchBegan(touch, event);
	return true;
}
void CollectionScene::onEnter(){
	Layer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(CollectionScene::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto mouseBinder = EventListenerMouse::create();
}
void CollectionScene::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}
