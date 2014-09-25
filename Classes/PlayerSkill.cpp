#include "PlayerSkill.h"
#include "CollectionScene.h"
<<<<<<< HEAD
#include "HelloWorldScene.h"
=======
#include "ShopScene.h"
>>>>>>> f3452533c050d43f53bb9736818cccd513ab7980
USING_NS_CC;

Texture2D *RoseKnife::starGraphic;

void RoseKnife::Init() {
    UIBase::Init();

    SkillSlot::Init("knife.png");

    starGraphic = Director::getInstance()->getTextureCache()->addImage("stars.png");
	decreaseRate = ST_DECREASE_RATE;
    skillName = "Incise";
}
void RoseKnife::Render() {
    SkillSlot::Render();

    skillIcon->setColor(dispColor);
}

void RoseKnife::activeSkill() {
    if (!Mouse::isDown() || Area::isAmid) {
        lastPoint = Vec2::ZERO;
        return;
    }
	if (Area::maxPlanaria < UnitBase::getCurrentPlNumber())
		return;
    Area::stamina -= decreaseRate;

    Vec2 tPos = Mouse::getPoint();

    if (lastPoint.isZero()) {
        lastPoint = tPos;
    }

    float segInterval = 10;

    float dist = tPos.getDistance(lastPoint);
    int segCount = dist / segInterval;
    float segDist = dist / segCount;
    Vec2 segAlign = (lastPoint - tPos).getNormalized();

    if (segCount <= 1) {
        segCount = 1;
    }

    if (dist < segInterval) {
        segAlign = Vec2::ZERO;
    }

    for (int i = 1; i <= segCount; i++) {
        auto particle = ParticleFlower::create();
        particle->setTexture(starGraphic);

        if (particle != NULL) {
            particle->setScale(0.3f);
            if (segAlign.isZero()) {
                particle->setPosition(Mouse::getPoint());
            }
            else {
                particle->setPosition(Mouse::getPoint() + (segAlign * (segDist * i)));
            }
            particle->setDuration(0.02f);

            UIBase::layer->addChild(particle);
        }
    }

    for (auto child : Planaria::Plas) {
        if (child->isCrash(tPos, 5)) {
            child->cutBody(tPos);
        }
    }

    lastPoint = Mouse::getPoint();
}

void ScoopPot::Init() {
    skillName = "Collect";

    SkillSlot::Init("scoop-pot.png");
}


void ScoopPot::activeSkill() {
    if (!Mouse::isDown()) return;

    Vec2 tPos = Mouse::getPoint();

    for (auto child : Planaria::Plas) {
        if (child->isCrash(tPos, 5)) {
            child->becomeCoin();
        }
    }
}

void ScoopPot::Render() {
    SkillSlot::Render();

    skillIcon->setColor(dispColor);
}

void BackToIntro::Init() {
    skillName = "Back to Intro";

    SkillSlot::Init("eye.png");
}


void BackToIntro::activeSkill() {
    if (!Mouse::isDown()) return;

    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void BackToIntro::Render() {
    SkillSlot::Render();

    skillIcon->setColor(dispColor);
}

void Decontaminant::Init(){
	skillName = "Nova";
	SkillSlot::Init("nova.png");
}

void Decontaminant::activeSkill(){
    Size visibleSize = Director::getInstance()->getVisibleSize();

    this->turnOff();
	if (Area::humanCoin < DECONTAMINANT_VALUE) return;
	Area::humanCoin -= DECONTAMINANT_VALUE;
	Area::ppm = 0;
    for (auto child : Poison::group) {
        child->setOver();
    }

    auto f = PoisonExEffect::create(10, 600);
    f->setPosition(visibleSize / 2);
}

void Decontaminant::Render(){
	SkillSlot::Render();
}

SkillSceneBtn::SkillSceneBtn(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	skillButtonSprite = Sprite::create("skillbutton.png");
	skillButtonSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	skillButtonSprite->setPosition(visibleSize.width, 0);
	layer->addChild(skillButtonSprite, Z_UI);
}

SkillSceneBtn::~SkillSceneBtn(){}

void SkillSceneBtn::gotoScene(){
	if (skillButtonSprite->getBoundingBox().containsPoint(Mouse::getPoint())){
		auto skillScene = CollectionScene::createScene();
		Director::getInstance()->pushScene(skillScene);
	}
}

ShopButton::ShopButton(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	shopButtonSprite = Sprite::create("shopbutton.png");
	shopButtonSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	shopButtonSprite->setPosition(visibleSize.width * 3 / 4, 0);
	layer->addChild(shopButtonSprite, Z_UI);
}
ShopButton::~ShopButton(){}

void ShopButton::gotoScene(){
	if (shopButtonSprite->getBoundingBox().containsPoint(Mouse::getPoint())){
		auto shopScene = ShopScene::createScene();
		Director::getInstance()->pushScene(shopScene);
	}
}