#include "HelloWorldScene.h"
#include "ResultScene.h"
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

    Size visibleSize = Director::getInstance()->getVisibleSize();

    statStamina->setProfileImgRate(Area::stamina / 100);

    if (Area::stamina < 0) {
        Area::isAmid = true;
        Area::amidTime = 400.f;
    }

    auto statCircle = statStamina->getProfileCircle();

    if (Area::isAmid) {

        statCircle->setColor(Color3B(255, 40, 40));

        if (Area::amidTime > 0) {
            Area::amidTime -= 1.f;
        }

        if (Area::amidTime <= 0) {
            Area::isAmid = false;
            Area::amidTime = 0;
        }
    }
    else {
        statCircle->setColor(Color3B(255, 255, 255));
    }

    Area::stamina += 0.05f;

    if (Area::stamina > 100) {
        Area::stamina = 100;
    }

    auto ppmImg = statPPM->getProfileImg();

    if (Area::ppm >= 100) {
        ppmImg->setColor(Color3B(100, 255, 100));

        if (t % 150 == 0) {
            auto pos = Poison::create(200 + getNext() * 200, 50 + getNext() * 50);

            pos->setPosition(visibleSize.width / 2 + 400 - getNext() * 800, visibleSize.height / 2 + 300 - getNext() * 600);
        }
    }
    else {
        ppmImg->setColor(Color3B(255, 255, 255));
    }

    auto goldLb = statGold->getLabel();
    goldLb->setString(to_string((int)Area::humanCoin));

    auto ppmLb = statPPM->getLabel();
    ppmLb->setString(to_string((int)Area::ppm));

    auto statLb = statStamina->getLabel();
    statLb->setString(to_string((int)Area::stamina) + " / 100");
    
    if (Planaria::Plas.size() <= 0) {
        Director::getInstance()->pushScene(ResultScene::createScene());
    }

    t++;
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

    Mouse::Initialize();
    
    Layer::onExit();
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event) {
    Mouse::onTouchBegan(touch, event);
	skillSceneButton->gotoScene();
	shopButton->gotoScene();
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

	ActionInterval* ripple = Ripple3D::create(60, Size(32, 32), visibleSize / 2, 800, 30, 15);

	auto nodeGrid = NodeGrid::create();
	nodeGrid->runAction(RepeatForever::create((Sequence*)Sequence::create(ripple, lens, NULL)));
	nodeGrid->addChild(bgimage);

	this->addChild(nodeGrid);

	auto systemUI = AreaUI::create();

	auto skill1 = RoseKnife::create();
	auto skill2 = ScoopPot::create();
	auto skill3 = Decontaminant::create();
	auto skillGroup = systemUI->getSkillGroup();

	skillGroup->addChild(skill1);
	skillGroup->addChild(skill2);
	skillGroup->addChild(skill3);
	skillGroup->alignItems();
	skill1->turnOn();

	skillSceneButton = new SkillSceneBtn();

	shopButton = new ShopButton();

	auto statGroup = systemUI->getStatGroup();

	auto profileTest = Profile::create("chat-man.png");

	statGold = Profile::create("coin.png");

	statPPM = Profile::create("ppm.png");

    statStamina = Profile::create("stamina.png");

    auto goldName = statGold->getName();
    goldName->setString("Gold");

    auto ppmName = statPPM->getName();
    ppmName->setString("PPM");

    auto statName = statStamina->getName();
    statName->setString("Stamina");

	statGroup->addChild(profileTest);
	statGroup->addChild(statGold);
	statGroup->addChild(statPPM);
	statGroup->addChild(statStamina);

	auto txt = statGold->getLabel();

	txt->setString("fewfw");

	statGroup->alignItems();

    Initialize();

	this->schedule(schedule_selector(HelloWorld::Mainloop));
	this->schedule(schedule_selector(HelloWorld::addNewPlanaria), 1.f);
}

void HelloWorld::Initialize() {

    Size visibleSize = Director::getInstance()->getVisibleSize();

    UnitBase::removeAll();

    for (int i = 0; i < 5; i++) {
        NormalPlanaria *pl2 = NormalPlanaria::create();
        ExtendedPlanaria *pl3 = ExtendedPlanaria::create();
        pl2->setMove((float)rand() / RAND_MAX * 360, 0.5);
        pl2->setPosition(visibleSize.width * (float)rand() / RAND_MAX, visibleSize.height * (float)rand() / RAND_MAX);
        pl3->setMove((float)rand() / RAND_MAX * 360, 0.5);
        pl3->setPosition(visibleSize.width * (float)rand() / RAND_MAX, visibleSize.height * (float)rand() / RAND_MAX);
    }

    Area::humanCoin = 0;
    Area::ppm = 0;
    Area::stamina = 100.f;
    Area::isAmid = false;
    Area::cutPlas = 0;
    Area::deadPlas = 0;
}
void HelloWorld::addNewPlanaria(float){
	if (Area::isNewPlanaria == false) return;
	NormalPlanaria* pl = NormalPlanaria::create();
	pl->setMove(getNext() * 360, 0.5);
	pl->setPosition(visibleSize.width * getNext(), visibleSize.height * getNext());
	Area::addedPlanaria[1] -= 1;
	if (Area::addedPlanaria[1] == 0)
		Area::isNewPlanaria = false;

}