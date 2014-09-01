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

void SkillSlot::Init(const string &iconName = string()) {
    UnitBase::Init();

    oDir = Director::getInstance();

    skillDisp = SpriteBatchNode::create("sprite.png");
    skillDisp->setGlobalZOrder(Z_UI);

    UnitBase::layer->addChild(skillDisp);

    skillBorder = Sprite::createWithSpriteFrameName("border-polygon.png");
    
    skillIcon = Sprite::createWithSpriteFrameName(iconName);
    skillDisp->addChild(skillIcon);

    skillDisp->addChild(skillBorder);
    skillDisp->setPosition(this->getPosition());

    dispColor = Color3B(255, 255, 255);

    skillLabel = LabelTTF::create(skillName, UI_FONT, 14.f);
    skillLabel->setPosition(skillDisp->getPositionX(), skillDisp->getPositionY() - btnRadius - 10.f);
    skillLabel->setGlobalZOrder(Z_UI);
    skillLabel->setLocalZOrder(Z_UI);
    UnitBase::layer->addChild(skillLabel, Z_UI);
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
    dispColor = Color3B(255, 255, 255);

    if (isActivated()) {
        dispColor = Color3B(100, 100, 255);
    }

    if (coolTime > 0) {
        dispColor = Color3B(100, 100, 100);
    }

    skillBorder->setColor(dispColor);
    if (skillIcon != nullptr) {
        skillIcon->setColor(dispColor);
    }

    skillLabel->setString(skillName);

    //skillLabel->setFontFillColor(dispColor);
    //skillLabel->setColor(dispColor);
}

void SkillSlot::Dead() {
    UnitBase::layer->removeChild(skillBorder);
    UnitBase::layer->removeChild(skillLabel);
    if (skillIcon != nullptr) {
        UnitBase::layer->removeChild(skillIcon);
    }
    UnitBase::layer->removeChild(skillDisp);
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

void AreaUI::Init() {
    UnitBase::Init();

    areaDisp = SpriteBatchNode::create("sprite.png");

    UnitBase::layer->addChild(areaDisp, Z_UI);

    borderTop = Sprite::createWithSpriteFrameName("area-border-top.png");
    borderBottom = Sprite::createWithSpriteFrameName("area-border-bottom.png");
    borderLeft = Sprite::createWithSpriteFrameName("area-border-left.png");
    borderRight = Sprite::createWithSpriteFrameName("area-border-right.png");

    areaDisp->addChild(borderTop);
    areaDisp->addChild(borderBottom);
    areaDisp->addChild(borderLeft);
    areaDisp->addChild(borderRight);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto cFrame = SpriteFrameCache::getInstance();

    auto topRect = cFrame->getSpriteFrameByName("area-border-top.png")->getRect();
    borderTop->setPosition(visibleSize.width / 2, visibleSize.height - topRect.size.height / 2);

    auto bottomRect = cFrame->getSpriteFrameByName("area-border-bottom.png")->getRect();
    borderBottom->setPosition(visibleSize.width / 2, bottomRect.size.height / 2);

    auto leftRect = cFrame->getSpriteFrameByName("area-border-left.png")->getRect();
    borderLeft->setPosition(leftRect.size.width / 2, visibleSize.height / 2);

    auto rightRect = cFrame->getSpriteFrameByName("area-border-left.png")->getRect();
    borderRight->setPosition(visibleSize.width - rightRect.size.width / 2, visibleSize.height / 2);
}