#include "PlayerSkill.h"

USING_NS_CC;

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

void roseKnife::Render() {
    QuickSlot::Render();
}

void roseKnife::skillSet() {
    if (!Mouse::isDown()) return;

    auto particle = ParticleFlower::create();

    auto texture = Director::getInstance()->getTextureCache()->addImage("stars.png");
    particle->setTexture(texture);

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