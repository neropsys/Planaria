#include "UI.h"

USING_NS_CC;

QuickSlot::QuickSlot() {
}

QuickSlot::~QuickSlot() {
}

void QuickSlot::Init() {
    UnitBase::Init();

    btnModel = DrawNode::create();

    UnitBase::layer->addChild(btnModel);

    oDir = Director::getInstance();
}

void QuickSlot::Run() {
    if (coolTime <= 0) {
        if (Mouse::isDown()) {
            float distX = Mouse::getPoint().x - position.x, distY = Mouse::getPoint().y - position.y;
            float realSize = btnRadius + 1;

            if ((distX * distX + distY * distY) < (realSize * realSize)) {
                if (isActivated()) {
                    this->turnOff();
                }
                else {
                    this->turnOn();
                }

                coolTime = 0.5f;
            }
        }

        if (this->isActivated()) {
            skillSet();
        }
    }

    if (coolTime > 0) {
        coolTime -= 1 / oDir->getFrameRate();

        if (coolTime < 0.1) {
            coolTime = 0;
        }
    }

    Render();
}

void QuickSlot::skillSet() {
}

void QuickSlot::Render() {
    btnModel->clear();

    btnModel->drawDot(this->position, this->btnRadius, Color4F(1, 1, 1, 1));
}

void QuickSlot::Dead() {
    UnitBase::layer->removeChild(btnModel);
}

void QuickSlot::turnOff() {
    actState = false;
}

void QuickSlot::turnOn() {
    actState = true;
}

QuickSlot *QuickSlot::create() {
    auto unit = new QuickSlot();

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

bool QuickSlot::isActivated() {
    return actState;
}