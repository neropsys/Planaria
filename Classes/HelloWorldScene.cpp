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

>>>>>>> parent of 3307072... something was wrong
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

    Planaria::Initialize(this);

    this->schedule(schedule_selector(HelloWorld::Mainloop));

    Planaria *test[100];

    for (int i = 0; i < 50; i++) {
        test[i] = Planaria::create(visibleSize.width * getNext(), visibleSize.height * getNext(), getNext() * 360);

        //log("%f, %f, %f", getNext(), visibleSize.height * getNext(), getNext() * 360);
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    /*auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

 
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
