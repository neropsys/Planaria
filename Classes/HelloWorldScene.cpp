#include "HelloWorldScene.h"
#include "SkillUpgradeScene.h"
USING_NS_CC;
using namespace cocos2d;
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

	auto skillButton = MenuItemImage::create("skillbutton.png", "skillbutton.png", CC_CALLBACK_1(HelloWorld::gotoSkillUpgradeScene, this));
	skillButton->setPosition(Point(500, -300));//hard-coded, needs to be changed

	auto Menu = Menu::create(skillButton, NULL);
	this->addChild(Menu);


    Planaria::Initialize(this);

    this->schedule(schedule_selector(HelloWorld::Mainloop));
	this->schedule(schedule_selector(HelloWorld::eachSecond), 1.0f);

        RainbowPlanaria *pl = RainbowPlanaria::create();
        NormalPlanaria *pl2 = NormalPlanaria::create();
        ExtendedPlanaria *pl3 = ExtendedPlanaria::create();
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
	g_scenePollution += g_pollutionIncreaseRate;
	log("current pollution of this scene :%f, increaseRate = %f", g_scenePollution, g_pollutionIncreaseRate);	
}

void HelloWorld::gotoSkillUpgradeScene(Ref* pSender){
	auto skillScene = SkillUpgradeScene::createScene();
	Director::getInstance()->pushScene(skillScene);
}