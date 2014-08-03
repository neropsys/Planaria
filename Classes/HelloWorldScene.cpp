#include "HelloWorldScene.h"

USING_NS_CC;
using namespace cocos2d;
float pollutionRate = 0.0f;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

float HelloWorld::getNext() {
    return (float)rand() / RAND_MAX;
}

void HelloWorld::Mainloop(float f) {
    Planaria::Mainloop();
}

void HelloWorld::onEnter() {
    Layer::onEnter();

    auto listener = EventListenerTouchOneByOne::create();

    listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto mouseBinder = EventListenerMouse::create();
}

void HelloWorld::onExit() {
    _eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
    
    Layer::onExit();
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event) {
    Planaria::onTouchBegan(touch, event);

    return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event) {
    Planaria::onTouchMoved(touch, event);

}

void HelloWorld::onTouchEnded(Touch* touch, Event* event) {
    Planaria::onTouchEnded(touch, event);
}

void HelloWorld::onTouchCancelled(Touch* touch, Event* event) {
    Planaria::onTouchCancelled(touch, event);
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	Vector<Planaria*> planarias;
    srand(time(NULL));
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Planaria::Initialize(this);

    this->schedule(schedule_selector(HelloWorld::Mainloop));
	this->schedule(schedule_selector(HelloWorld::eachSecond), 1.0f);

    //for (int i = 0; i < 1; i++) {
        RainbowPlanaria *pl = RainbowPlanaria::create();
        NormalPlanaria *pl2 = NormalPlanaria::create();
        ExtendedPlanaria *pl3 = ExtendedPlanaria::create();
        /*pl->setMove(getNext() * 360, 1);
        pl->setPosition(visibleSize.width * getNext(), visibleSize.height * getNext());
        pl2->setMove(getNext() * 360, 1);
        pl2->setPosition(visibleSize.width * getNext(), visibleSize.height * getNext());
        pl3->setMove(getNext() * 360, 1);
        pl3->setPosition(visibleSize.width * getNext(), visibleSize.height * getNext());*/
   // }
		planarias.pushBack(pl);
		planarias.pushBack(pl2);
		planarias.pushBack(pl3);
		for (Vector<Planaria*>::iterator it = planarias.begin(); it != planarias.end(); it++){
			(*it)->setMove(getNext()*360, 1);
			(*it)->setPosition(visibleSize.width*getNext(), visibleSize.height*getNext());
		}
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::eachSecond(float f){
	pollutionRate += 1.0f;
	log("pollutionRate :%f", pollutionRate);
	
}