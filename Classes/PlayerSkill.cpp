#include "PlayerSkill.h"

USING_NS_CC;

Texture2D *roseKnife::starGraphic;

void roseKnife::Init() {
    UIBase::Init();

    SkillSlot::Init("knife.png");

    starGraphic = Director::getInstance()->getTextureCache()->addImage("stars.png");

    skillName = "Incise";
}

void roseKnife::Render() {
    SkillSlot::Render();

    skillIcon->setColor(dispColor);
}

void roseKnife::activeSkill() {
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

void scoopPot::Init() {
    skillName = "Collect";

    SkillSlot::Init("scoop-pot.png");
}

void scoopPot::activeSkill() {
    //log("%f, %f", this->getPositionX(), this->getPositionY());

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

    skillIcon->setColor(dispColor);
}