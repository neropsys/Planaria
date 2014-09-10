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
<<<<<<< HEAD
    UnitBase::Mainloop();
=======
    UIBase::Mainloop();

    
    //log("%d", stat3);

    statStamina->setProfileImgRate(Area::stamina / 100);
    /*NodeGrid *nodeGrid = (NodeGrid *)getChildByName("node");

    auto size = Size(32, 32);

    auto grid = GridBase::create(size);
    nodeGrid->setGrid(grid);

    auto g = (Grid3D *)grid;
    auto key = Vec2(2, 2);

    auto tile = g->getOriginalVertex(key);

    g->setVertex(key, tile);*/
>>>>>>> origin/Planaria-Redesign
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
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
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
<<<<<<< HEAD
    UnitBase::Initialize(this);

    this->schedule(schedule_selector(HelloWorld::Mainloop));
=======
>>>>>>> origin/Planaria-Redesign

    for (int i = 0; i < 5; i++) {
        //RainbowPlanaria *pl = RainbowPlanaria::create();
        NormalPlanaria *pl2 = NormalPlanaria::create();
        ExtendedPlanaria *pl3 = ExtendedPlanaria::create();
        //pl->setMove(getNext() * 360, 1);
        //pl->setPosition(visibleSize.width * getNext(), visibleSize.height * getNext());
        pl2->setMove(getNext() * 360, 1);
        pl2->setPosition(visibleSize.width * getNext(), visibleSize.height * getNext());
        pl3->setMove(getNext() * 360, 1);
        pl3->setPosition(visibleSize.width * getNext(), visibleSize.height * getNext());
    }


    auto systemUI = AreaUI::create();

<<<<<<< HEAD
    SpriteBatchNode *profile = SpriteBatchNode::create("sprite.png");
    auto sp1 = Sprite::createWithSpriteFrameName("chat-circle.png");
    profile->addChild(sp1);

    auto sp2 = Sprite::createWithSpriteFrameName("chat-man.png");
    profile->addChild(sp2);

    profile->setPosition(40, 40);

    this->addChild(profile);

    auto skill1 = RoseKnife::create();
    auto skill2 = ScoopPot::create();
=======
    auto skill1 = roseKnife::create();
    auto skill2 = scoopPot::create();
>>>>>>> origin/Planaria-Redesign

    auto skillGroup = systemUI->getSkillGroup();

	skillSceneButton = new SkillSceneBtn();
	skillSceneButton->setGlobalZOrder(100);
	this->addChild(skillSceneButton);

    skillGroup->addChild(skill1);
    skillGroup->addChild(skill2);
<<<<<<< HEAD
	skillGroup->setPosition(256, 48);
=======
>>>>>>> origin/Planaria-Redesign

    skillGroup->alignItems();

    skill1->turnOn();

<<<<<<< HEAD
    Area::coinLabel = LabelTTF::create("0", "Segoe UI", 36);
    Area::coinLabel->setPosition(128, visibleSize.height - 32);
    Area::coinLabel->setHorizontalAlignment(TextHAlignment::LEFT);
=======
    auto statGroup = systemUI->getStatGroup();

    auto profileTest = Profile::create("chat-man.png");

    statGold = Profile::create("coin.png");

    statPPM = Profile::create("ppm.png");

    statStamina = Profile::create("stamina.png");

    //log("%s", stat3->getName().c_str());

    statGroup->addChild(profileTest);
    statGroup->addChild(statGold);
    statGroup->addChild(statPPM);
    statGroup->addChild(statStamina);

    auto txt = statGold->getLabel();

    txt->setString("fewfw");

    statGroup->alignItems();

    this->schedule(schedule_selector(HelloWorld::Mainloop));

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
>>>>>>> origin/Planaria-Redesign

    this->addChild(Area::coinLabel);



    
    return true;
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
