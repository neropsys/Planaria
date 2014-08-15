#include "UnitBase.h"

USING_NS_CC;

Vector<UnitBase *> UnitBase::newUnit;
Vector<UnitBase *> UnitBase::crtUnit;
Vector<UnitBase *> UnitBase::deadUnit;

Layer *UnitBase::layer;

UnitBase::UnitBase() {
}

UnitBase::~UnitBase() {
}

void UnitBase::Initialize(Layer *layer) {
    UnitBase::layer = layer;
}

void UnitBase::Mainloop() {
    // create planarias
    for (auto child : newUnit) {
        crtUnit.pushBack(child);

        child->Init();
    }
    newUnit.clear();

    for (auto child : crtUnit) {
        child->Run();
    }

    //log("%d", callCount);

    // kill planarias
    for (auto child : deadUnit) {
        child->Dead();

        crtUnit.eraseObject(child, false);
    }

    deadUnit.clear();
}

void UnitBase::Finalize() {
}

void UnitBase::Init() {
}

void UnitBase::Run() {
}

void UnitBase::Coll(UnitBase *other) {
}

void UnitBase::Dead() {
}

void UnitBase::Final() {
}

void UnitBase::Die() {
    deadUnit.pushBack(this);
}

bool UnitBase::onTouchBegan(Touch* touch, Event* event) {
    Vec2 tPos = touch->getLocation();

    return true;
}

void UnitBase::onTouchMoved(Touch* touch, Event* event) {
    Vec2 tPos = touch->getLocation();
}

void UnitBase::onTouchEnded(Touch* touch, Event* event) {
}

void UnitBase::onTouchCancelled(Touch* touch, Event* event) {
}

UnitBase *UnitBase::create() {
    auto unit = new UnitBase();

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