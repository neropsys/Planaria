#include "HelloWorldScene.h"

USING_NS_CC;

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
    UnitBase::Mainloop();
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
    Mouse::onTouchBegan(touch, event);

    return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event) {
    Mouse::onTouchMoved(touch, event);
    auto test = ParticleFlower::create();
    test->setPosition(touch->getLocation());
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event) {
    Mouse::onTouchEnded(touch, event);
}

void HelloWorld::onTouchCancelled(Touch* touch, Event* event) {
    Mouse::onTouchCancelled(touch, event);
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    srand(time(NULL));
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    UnitBase::Initialize(this);

    this->schedule(schedule_selector(HelloWorld::Mainloop));

    for (int i = 0; i < 5; i++) {
        RainbowPlanaria *pl = RainbowPlanaria::create();
        NormalPlanaria *pl2 = NormalPlanaria::create();
        ExtendedPlanaria *pl3 = ExtendedPlanaria::create();
        pl->setMove(getNext() * 360, 1);
        pl->setPosition(visibleSize.width * getNext(), visibleSize.height * getNext());
        pl2->setMove(getNext() * 360, 1);
        pl2->setPosition(visibleSize.width * getNext(), visibleSize.height * getNext());
        pl3->setMove(getNext() * 360, 1);
        pl3->setPosition(visibleSize.width * getNext(), visibleSize.height * getNext());
    }

    auto skill1 = roseKnife::create();

    skill1->setPosition(32, 32);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    /*auto knifeSkillOff = MenuItemImage::create(
        "weapon/rose-knife-off.png",
        "weapon/rose-knife-off.png",
        NULL,
        NULL);

    auto knifeSkillOn = MenuItemImage::create(
        "weapon/rose-knife-on.png",
        "weapon/rose-knife-on.png",
        NULL,
        NULL);

    auto roseKnife = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HelloWorld::weaponMenuCallback, this), knifeSkillOff, knifeSkillOn, NULL);
    roseKnife->setName("roseKnife");

    auto scoopOff = MenuItemImage::create(
        "weapon/scoop-pot-off.png",
        "weapon/scoop-pot-off.png",
        NULL,
        NULL);

    auto scoopOn = MenuItemImage::create(
        "weapon/scoop-pot-on.png",
        "weapon/scoop-pot-on.png",
        NULL,
        NULL);

    auto scoopPot = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HelloWorld::weaponMenuCallback, this), scoopOff, scoopOn, NULL);
    scoopPot->setName("scoopPot");

    // create menu, it's an autorelease object
    auto menu = Menu::create(roseKnife, scoopPot, NULL);
    menu->setPosition(128, 64);
    this->addChild(menu, 1);
    menu->setTag(_WEAPON_);
    menu->alignItemsHorizontally();

    roseKnife->activate();*/

    /*
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);*/
    
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

void HelloWorld::weaponMenuCallback(Ref *pSender) {
    MenuItemToggle *pMenu = (MenuItemToggle *)pSender;
    Menu *menuParent = (Menu *)getChildByTag(_WEAPON_);

    for (auto child : menuParent->getChildren()) {
        MenuItemImage *realChild = (MenuItemImage *)child;

        if (pMenu == child) {
        }
        else {
        }
    }
}