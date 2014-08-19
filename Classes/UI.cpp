#include "UI.h"

USING_NS_CC;

ItemSlot::ItemSlot() {
}

ItemSlot::~ItemSlot() {
}

void ItemSlot::alignItems() {
    Vector<Node *> items = getChildren();

    int dist = 0;

    for (auto item : items) {
        UnitBase *child = (UnitBase *)item;

        child->setPosition(this->getPosition().x + dist, this->getPosition().y);

        dist += child->getSize() * 2 + margin;
    }
}

/*RadioSlot *RadioSlot::create() {
    auto unit = new RadioSlot();

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
}*/

void RadioSlot::addChild(Node *child)
{
    Node::addChild(child);

    ((QuickSlot *)child)->setGroup(this);
}

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
    if (Mouse::isDown() && coolTime <= 0 && Mouse::isFirst()) {
        float distX = Mouse::getPoint().x - position.x, distY = Mouse::getPoint().y - position.y;
        float realSize = btnRadius + 1;

        if ((distX * distX + distY * distY) < (realSize * realSize)) {
            if (isActivated()) {
                this->turnOff();
            }
            else {
                // if it is in a radio group, other items need to be turned off.
                if (this->radioGroup != nullptr) {

                    for (auto child : this->radioGroup->getChildren()) {
                        QuickSlot *realChild = (QuickSlot *)child;

                        realChild->turnOff();
                        realChild->setCoolTime(0.5f);
                    }
                }

                this->turnOn();
            }

            coolTime = 0.5f;
        }
    }

    if (this->isActivated() && coolTime <= 0) {
        activeSkill();
    }

    passiaveSkill();

    if (coolTime > 0) {
        coolTime -= 1 / oDir->getFrameRate();

        if (coolTime < 0.1) {
            coolTime = 0;
        }
    }

    Render();
}

void QuickSlot::setCoolTime(float time) {
    coolTime = time;
}

void QuickSlot::activeSkill() {
}


void QuickSlot::passiaveSkill() {
}

void QuickSlot::Render() {
    btnModel->clear();

    Color4F btnColor = Color4F(1.f, 1.f, 1.f, 1.f);

    if (this->isActivated()) {
        btnColor = Color4F(1.f, 0.f, 0.f, 1.f);
    }

    if (coolTime > 0) {
        btnColor = Color4F(0.3f, 0.3f, 0.3f, 1.f);
    }

    btnModel->drawDot(this->position, this->btnRadius, btnColor);
}

void QuickSlot::Dead() {
    UnitBase::layer->removeChild(btnModel);
}

float QuickSlot::getSize() {
    return btnRadius;
}

void QuickSlot::setGroup(RadioSlot *group) {
    this->radioGroup = group;
}

RadioSlot *QuickSlot::getGroup() {
    return this->radioGroup;
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