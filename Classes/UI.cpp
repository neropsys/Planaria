#include "UI.h"

USING_NS_CC;

Vector<UIBase *> UIBase::UICont, UIBase::UIDead, UIBase::UIQueue;
Layer *UIBase::layer;

UIBase::UIBase() {
}

void UIBase::Initialize(Layer *layer) {
    UIBase::layer = layer;

    UnitBase::Initialize(layer);
}

void UIBase::Mainloop() {
    UnitBase::Mainloop();

    for (auto child : UIQueue) {
        UICont.pushBack(child);

        child->Init();
    }
    UIQueue.clear();

    for (auto child : UICont) {
        child->Run();
    }

    for (auto child : UIDead) {
        child->Dead();

        UICont.eraseObject(child, false);
    }

    UIDead.clear();
}

void UIBase::Init() {
}

void UIBase::Run() {
    if (Rect(getPositionX() - getBoxModel().width / 2, getPositionY() - getBoxModel().height / 2, getBoxModel().width, getBoxModel().height).intersectsRect(Rect(Mouse::getPoint().x, Mouse::getPoint().y, 1, 1))) {
        if (Mouse::isDown()) {
            if (Mouse::isFirst()) {
                this->Click();
            }

            this->Drag();
        }
    }

    this->Render();
}

void UIBase::Dead() {
}

void UIBase::Click() {
}

void UIBase::Drag() {
}

void UIBase::Render() {
}

Size &UIBase::getBoxModel() {
    return boxModel;
}

Size &UIBase::setBoxModel(const Size &size) {
    boxModel = size;

    return getBoxModel();
}

void SlotGroup::alignItems() {
    Vector<Node *> items = getChildren();

    int dist = 0;

    for (auto item : items) {
        UIBase *child = (UIBase *)item;

        Vec2 childPos = Vec2(this->getPosition().x + dist, this->getPosition().y);
        child->setPosition(childPos);

        dist += child->getBoxModel().width + margin;
    }
}

Vec2 &SlotGroup::getNextPosition() {
    Vec2 nextPos;
    
    return nextPos;
}

void SlotGroup::addChildWithAction(cocos2d::Node *child) {
    Node::addChild(child);
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

    UIBase::newUnit.pushBack(unit);

    return unit;
}*/

void RadioGroup::addChild(Node *child)
{
    Node::addChild(child);

    ((SkillSlot *)child)->setGroup(this);
}

SkillSlot::SkillSlot() {
    setBoxModel(Size(55, 55));
}

SkillSlot::~SkillSlot() {
}

void SkillSlot::Init(const string &iconName = string()) {
    UIBase::Init();

    oDir = Director::getInstance();

    skillDisp = SpriteBatchNode::create("sprite.png");
    skillDisp->setGlobalZOrder(Z_UI);
    skillDisp->setPosition(this->getPosition());

    UIBase::layer->addChild(skillDisp);

    skillBorder = Sprite::createWithSpriteFrameName("border-polygon.png");
    skillDisp->addChild(skillBorder);
    
    skillIcon = Sprite::createWithSpriteFrameName(iconName);
    skillDisp->addChild(skillIcon);

    dispColor = Color3B(255, 255, 255);

    skillLabel = LabelTTF::create(skillName, UI_FONT, 14.f);
    skillLabel->setGlobalZOrder(Z_UI);
    skillLabel->setLocalZOrder(Z_UI);
    skillLabel->setPosition(this->getPosition());
    UIBase::layer->addChild(skillLabel, Z_UI);

    Render();
}

void SkillSlot::Click() {
    if (coolTime > 0) {
        return;
    }

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

void SkillSlot::Run() {
    UIBase::Run();

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

    if (!(this->getPosition() - skillDisp->getPosition()).isZero()) {
        if (skillDisp->getNumberOfRunningActions() <= 0) {
            skillDisp->runAction(EaseOut::create(MoveTo::create(0.5f, this->getPosition()), 2.5f));
        }
    }

    //skillDisp->setPosition(this->getPosition());

    skillLabel->setPosition(skillDisp->getPositionX(), skillDisp->getPositionY() - getBoxModel().height / 2 - 10.f);
    //skillLabel->setFontFillColor(dispColor);
    //skillLabel->setColor(dispColor);

    //log("%f, %f", this->getPositionX(), this->getPositionY());
}

void SkillSlot::Dead() {
    UIBase::layer->removeChild(skillBorder);
    UIBase::layer->removeChild(skillLabel);
    if (skillIcon != nullptr) {
        UIBase::layer->removeChild(skillIcon);
    }
    UIBase::layer->removeChild(skillDisp);
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

bool SkillSlot::isActivated() {
    return actState;
}

AreaUI::AreaUI() {

    areaDisp = SpriteBatchNode::create("sprite.png");

    UIBase::layer->addChild(areaDisp, Z_UI);

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

    navGroup = SlotGroup::create();
    UIBase::layer->addChild(navGroup, Z_UI);

    statGroup = SlotGroup::create();
    UIBase::layer->addChild(statGroup, Z_UI);

    skillGroup = RadioGroup::create();
    UIBase::layer->addChild(skillGroup, Z_UI);

    statGroup->setPosition(64, 48);

    statGroup->alignItems();

    skillGroup->setPosition(-128, 54);

    skillGroup->alignItems();
}

AreaUI::~AreaUI() {

}

void AreaUI::Init() {
    UIBase::Init();

    statGroup->alignItems();

    auto statChildren = statGroup->getChildren();

    auto statLastChild = (UIBase *)statChildren.back();

    skillGroup->setPosition(statGroup->getPositionX() + statLastChild->getPositionX() + statLastChild->getBoxModel().width / 2, skillGroup->getPositionY());

    skillGroup->alignItems();
}

void AreaUI::Dead() {
    areaDisp->removeAllChildren();
    UIBase::layer->removeChild(areaDisp);

    UIBase::layer->removeChild(navGroup);
    UIBase::layer->removeChild(statGroup);
    UIBase::layer->removeChild(skillGroup);
}

SlotGroup *AreaUI::getNavGroup() {
    return navGroup;
}

SlotGroup *AreaUI::getStatGroup() {
    return statGroup;
}

RadioGroup *AreaUI::getSkillGroup() {
    return skillGroup;
}

void AreaUI::Run()
{
    auto statChildren = statGroup->getChildren();

    auto statLastChild = (UIBase *)statChildren.back();

    skillGroup->setPosition(statGroup->getPositionX() + statLastChild->getPositionX() + statLastChild->getBoxModel().width / 2, skillGroup->getPositionY());

    skillGroup->alignItems();
}

Profile *Profile::create(const string &profileImage) {
    Profile *prof = Profile::create();

    prof->profileImgName = profileImage;

    return prof;
}

Profile::Profile() {
    this->setBoxModel(Size(116, 116));

    profileDisp = SpriteBatchNode::create("sprite.png");

    UIBase::layer->addChild(profileDisp, Z_UI);

    profileCircle = Sprite::createWithSpriteFrameName("chat-circle.png");
    profileDisp->addChild(profileCircle);

    if (this->profileImgName.size() <= 0) {
        this->profileImgName = "chat-man.png";
    }

    profileImg = Sprite::createWithSpriteFrameName(profileImgName);
    profileDisp->addChild(profileImg);

    profileText = LabelTTF::create("", UI_FONT, 14.f);
    UIBase::layer->addChild(profileText, Z_UI);

}

Profile::~Profile() {
}

void Profile::Init() {
    UIBase::Init();
}

void Profile::setProfileImgRate(float rate) {
    profileImgRate = rate;
}

void Profile::Render() {
    SpriteFrame *profileImgFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(profileImgName);

    profileImg->setSpriteFrame(profileImgFrame);

    profileDisp->setPosition(this->getPosition());

    profileText->setPosition(this->getPosition());

    auto stat1sp = getProfileImg();
    
    auto editedRect = stat1sp->getTextureRect();

    if (originalSize.width == 0 && originalSize.height == 0) {
        originalSize = editedRect.size;
    }
    else {
        editedRect.size = originalSize;
    }

    editedRect.size.height *= profileImgRate;
    editedRect.setRect(editedRect.getMinX(), editedRect.getMinY() + originalSize.height - editedRect.size.height, editedRect.size.width, editedRect.size.height);

    stat1sp->setTextureRect(editedRect);
    //stat1sp->setAnchorPoint(Vec2(0, -originalSize.height - editedRect.size.height));
    stat1sp->setAnchorPoint(Vec2(0.5, 0.5 + 1 - profileImgRate));
    //log("%f, %f", stat1sp->getAnchorPoint().x, stat1sp->getAnchorPoint().y);
}