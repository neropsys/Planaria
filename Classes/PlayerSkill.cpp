#include "PlayerSkill.h"
#include "SkillUpgradeScene.h"
USING_NS_CC;

Texture2D *roseKnife::starGraphic;

roseKnife::roseKnife() {
}

roseKnife::~roseKnife() {
}

roseKnife *roseKnife::create() {
    auto unit = new roseKnife();

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

void roseKnife::Init() {
    UnitBase::Init();
    SkillSlot::Init();
    starGraphic = Director::getInstance()->getTextureCache()->addImage("stars.png");
}

void roseKnife::Render() {
    SkillSlot::Render();
}

void roseKnife::activeSkill() {
    if (!Mouse::isDown()) {
        lastPoint = Vec2::ZERO;
        return;
    }

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

            UnitBase::layer->addChild(particle);
        }
    }

    for (auto child : Planaria::Plas) {
        if (child->isCrash(tPos, 5)) {
            child->cutBody(tPos);
        }
    }

    lastPoint = Mouse::getPoint();
}

void scoopPot::activeSkill() {
    if (!Mouse::isDown()) return;

    Vec2 tPos = Mouse::getPoint();

    for (auto child : Planaria::Plas) {
        if (child->isCrash(tPos, 5)) {
            child->becomeCoin();
        }
    }
}

void scoopPot::Render() {
    SkillSlot::Render();
}
skillSceneBtn::skillSceneBtn(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	skillButtonSprite = Sprite::create("skillbutton.png");
	skillButtonSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	skillButtonSprite->setPosition(visibleSize.width, 0);
	layer->addChild(skillButtonSprite);
}
skillSceneBtn::~skillSceneBtn(){

}
void skillSceneBtn::gotoScene(){
	if (skillButtonSprite->getBoundingBox().containsPoint(Mouse::getPoint())){
		auto skillScene = SkillUpgradeScene::createScene();
		Director::getInstance()->pushScene(skillScene);
	}
}