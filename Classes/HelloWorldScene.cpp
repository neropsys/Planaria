#include "HelloWorldScene.h"
#include "Mouse.h"
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
    UIBase::Mainloop();

    statStamina->setProfileImgRate(Area::stamina / 100);
   
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
	skillSceneButton->gotoScene();
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
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite.plist");

	UIBase::Initialize(this);

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
	for (int i = 0; i < 5; i++) {
		NormalPlanaria *pl2 = NormalPlanaria::create();
		ExtendedPlanaria *pl3 = ExtendedPlanaria::create();
		pl2->setMove(getNext() * 360, 1);
		pl2->setPosition(visibleSize.width * getNext(), visibleSize.height * getNext());
		pl3->setMove(getNext() * 360, 1);
		pl3->setPosition(visibleSize.width * getNext(), visibleSize.height * getNext());
	}


	auto systemUI = AreaUI::create();

	auto skill1 = RoseKnife::create();
	auto skill2 = ScoopPot::create();

	auto skillGroup = systemUI->getSkillGroup();

	skillSceneButton = new SkillSceneBtn();
	skillSceneButton->setGlobalZOrder(100);
	this->addChild(skillSceneButton);

	skillGroup->addChild(skill1);
	skillGroup->addChild(skill2);
	skillGroup->alignItems();
	skill1->turnOn();

	auto statGroup = systemUI->getStatGroup();

	auto profileTest = Profile::create("chat-man.png");

	statGold = Profile::create("coin.png");

	statPPM = Profile::create("ppm.png");

	statStamina = Profile::create("stamina.png");



	statGroup->addChild(profileTest);
	statGroup->addChild(statGold);
	statGroup->addChild(statPPM);
	statGroup->addChild(statStamina);

	auto txt = statGold->getLabel();

	txt->setString("fewfw");

	statGroup->alignItems();

	this->schedule(schedule_selector(HelloWorld::Mainloop));
}