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
    if (!Mouse::isDown()) {
        lastPoint = Vec2::ZERO;
        return;
    }

<<<<<<< HEAD
    /*auto particle = ParticleFlower::create();
=======
    Vec2 tPos = Mouse::getPoint();
>>>>>>> origin/Planaria-Redesign

    if (lastPoint.isZero()) {
        lastPoint = tPos;
    }

    float segInterval = 10;

    float dist = tPos.getDistance(lastPoint);
    int segCount = dist / segInterval;
    float segDist = dist / segCount;
    Vec2 segAlign = (lastPoint - tPos).getNormalized();

<<<<<<< HEAD
        UnitBase::layer->addChild(particle);
    }*/
=======
    if (segCount <= 1) {
        segCount = 1;
    }
>>>>>>> origin/Planaria-Redesign

    if (dist < segInterval) {
        segAlign = Vec2::ZERO;
    }

    for (int i = 1; i <= segCount; i++) {

        auto particle = ParticleFlower::create();
        //log("%d", particle->getReferenceCount());
        particle->setTexture(starGraphic);
        
        if (particle != NULL) {
            particle->setScale(0.2f);
            if (segAlign.isZero()) {
                particle->setPosition(Mouse::getPoint());
            }
            else {
                particle->setPosition(Mouse::getPoint() + (segAlign * (segDist * i)));
            }

            //log("%f, %f", segAlign.x, segAlign.y);
            //log("%f, %f", particle->getPositionX(), particle->getPositionY());

            particle->setDuration(0.05f);

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
    QuickSlot::Render();
}