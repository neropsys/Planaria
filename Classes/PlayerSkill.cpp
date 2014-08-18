#include "PlayerSkill.h"

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
    QuickSlot::Init();
    starGraphic = Director::getInstance()->getTextureCache()->addImage("stars.png");
}

void roseKnife::Render() {
    QuickSlot::Render();
}

void roseKnife::activeSkill() {
    if (!Mouse::isDown()) return;

    auto particle = ParticleFlower::create();
    //log("%d", particle->getReferenceCount());
    particle->setTexture(starGraphic);

    if (particle != NULL) {
        particle->setScale(0.2f);
        particle->setPosition(Mouse::getPoint());

        particle->setDuration(0.1f);

        UnitBase::layer->addChild(particle);
    }

    Vec2 tPos = Mouse::getPoint();

    for (auto child : Planaria::Plas) {
        if (child->isCrash(tPos, 5)) {
            child->cutBody(tPos);
        }
    }
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
    QuickSlot::Render();
}