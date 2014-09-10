#include "PlayerSkill.h"
#include "CollectionScene.h"
USING_NS_CC;

Texture2D *RoseKnife::starGraphic;

<<<<<<< HEAD
RoseKnife::RoseKnife() {
}

RoseKnife::~RoseKnife() {
}

RoseKnife *RoseKnife::create() {
    auto unit = new RoseKnife();

    if (unit)
    {
        unit->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(unit);
    }

    UnitBase::newUnit.pushBack(unit);

    return unit;
}

void RoseKnife::Init() {
    UnitBase::Init();
=======
void roseKnife::Init() {
    UIBase::Init();
>>>>>>> origin/Planaria-Redesign

    SkillSlot::Init("knife.png");

    starGraphic = Director::getInstance()->getTextureCache()->addImage("stars.png");

    skillName = "Incise";
}

void RoseKnife::Render() {
    SkillSlot::Render();

    skillIcon->setColor(dispColor);
}

void RoseKnife::activeSkill() {
    if (!Mouse::isDown()) {
        lastPoint = Vec2::ZERO;
        return;
    }

    Area::stamina -= 0.5f;

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
        //log("%d", particle->getReferenceCount());
        particle->setTexture(starGraphic);

        if (particle != NULL) {
            particle->setScale(0.3f);
            if (segAlign.isZero()) {
                particle->setPosition(Mouse::getPoint());
            }
            else {
                particle->setPosition(Mouse::getPoint() + (segAlign * (segDist * i)));
            }

            //log("%f, %f", segAlign.x, segAlign.y);
            //log("%f, %f", particle->getPositionX(), particle->getPositionY());

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

<<<<<<< HEAD
void ScoopPot::activeSkill() {
=======
void scoopPot::activeSkill() {
    //log("%f, %f", this->getPositionX(), this->getPositionY());

>>>>>>> origin/Planaria-Redesign
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
SkillSceneBtn::SkillSceneBtn(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	skillButtonSprite = Sprite::create("skillbutton.png");
	skillButtonSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	skillButtonSprite->setPosition(visibleSize.width, 0);
	layer->addChild(skillButtonSprite, 101);
}
SkillSceneBtn::~SkillSceneBtn(){

}
void SkillSceneBtn::gotoScene(){
	if (skillButtonSprite->getBoundingBox().containsPoint(Mouse::getPoint())){
		auto skillScene = CollectionScene::createScene();
		Director::getInstance()->pushScene(skillScene);
	}
}