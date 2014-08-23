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


    auto bgimage = Sprite::create("background/fishtank.png");

    bgimage->setPosition(visibleSize / 2);
    bgimage->setScale(1.35f);
    // create a Lens3D action
    ActionInterval* lens = Lens3D::create(5, Size(32, 32), visibleSize / 2, 160);

        // create a Waved3D action
    ActionInterval* waves = Waves3D::create(60, Size(32, 32), 18, 15);

    ActionInterval* ripple = Ripple3D::create(60, Size(32, 32), visibleSize / 2, 800, 100, 100);

    auto nodeGrid = NodeGrid::create();

    nodeGrid->runAction(RepeatForever::create((Sequence*)Sequence::create(ripple, lens, NULL)));

    nodeGrid->addChild(bgimage);

    this->addChild(nodeGrid);
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
    auto skill2 = scoopPot::create();

    auto skillGroup = RadioGroup::create();

    skillGroup->addChild(skill1);
    skillGroup->addChild(skill2);

    skillGroup->setPosition(256, 48);

    skillGroup->alignItems();

    skill1->turnOn();


    Area::coinLabel = LabelTTF::create("0", "Segoe UI", 36);
    Area::coinLabel->setPosition(128, visibleSize.height - 32);
    Area::coinLabel->setHorizontalAlignment(TextHAlignment::LEFT);

    this->addChild(Area::coinLabel);
    
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
