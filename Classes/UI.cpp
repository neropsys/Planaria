#include "UI.h"

USING_NS_CC;

SlotGroup::SlotGroup() {
}

SlotGroup::~SlotGroup() {
}

void SlotGroup::alignItems() {
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

void RadioGroup::addChild(Node *child)
{
    Node::addChild(child);

    ((SkillSlot *)child)->setGroup(this);
}

SkillSlot::SkillSlot() {
}

SkillSlot::~SkillSlot() {
}

void SkillSlot::Init() {
    UnitBase::Init();

    btnModel = DrawNode::create();

    UnitBase::layer->addChild(btnModel);

    oDir = Director::getInstance();
}

void SkillSlot::Run() {
    if (Mouse::isDown() && coolTime <= 0 && Mouse::isFirst()) {
        float distX = Mouse::getPoint().x - getPositionX(), distY = Mouse::getPoint().y - getPositionY();
        float realSize = btnRadius + 1;

        if ((distX * distX + distY * distY) < (realSize * realSize)) {
            if (isActivated()) {
                this->turnOff();
            }
            else {
                // if it is in a radio group, other items need to be turned off.
                if (this->radioGroup != nullptr) {

                    for (auto child : this->radioGroup->getChildren()) {
                        SkillSlot *realChild = (SkillSlot *)child;

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

void SkillSlot::setCoolTime(float time) {
    coolTime = time;
}

void SkillSlot::activeSkill() {
}


void SkillSlot::passiaveSkill() {
}

void SkillSlot::Render() {
    btnModel->clear();

    Color4F btnColor = Color4F(1.f, 1.f, 1.f, 1.f);

    if (this->isActivated()) {
        btnColor = Color4F(1.f, 0.f, 0.f, 1.f);
    }

    if (coolTime > 0) {
        btnColor = Color4F(0.3f, 0.3f, 0.3f, 1.f);
    }

    btnModel->drawDot(this->getPosition(), this->btnRadius, btnColor);
}

void SkillSlot::Dead() {
    UnitBase::layer->removeChild(btnModel);
}

float SkillSlot::getSize() {
    return btnRadius;
}

void SkillSlot::setGroup(RadioGroup *group) {
    this->radioGroup = group;
}

RadioGroup *SkillSlot::getGroup() {
    return this->radioGroup;
}

void SkillSlot::turnOff() {
    actState = false;
}

void SkillSlot::turnOn() {
    actState = true;
}

SkillSlot *SkillSlot::create() {
    auto unit = new SkillSlot();

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

bool SkillSlot::isActivated() {
    return actState;
}