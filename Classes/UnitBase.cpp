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

void UnitBase::setAngle(float angle) {
    this->angle = angle;

    setVelocity();
}

float UnitBase::getAngle() {
    return angle;
}

void UnitBase::setSpeed(float speed) {
    this->speed = speed;

    setVelocity();
}

float UnitBase::getSpeed() {
    return speed;
}

void UnitBase::setPosition(float x, float y) {
    this->position.x = x;
    this->position.y = y;
}

Vec2 &UnitBase::getPosition() {
    return position;
}

void UnitBase::setVelocity() {
    velocity.setPoint(cosf(RAD(angle)) * speed, -sinf(RAD(angle)) * speed);
}

bool UnitBase::isCrash(const Vec2 &pt, float radius) {
    return isCrash(pt.x, pt.y, radius);
}

bool UnitBase::isCrash(float x, float y, float radius) {
    float distX = x - position.x, distY = y - position.y;
    float realSize = radius + bodySize;

    if ((distX * distX + distY * distY) < (realSize * realSize)) {
        return true;
    }

    return false;
}

void UnitBase::setMove(float angle, float speed) {
    velocity.setPoint(cosf(RAD(angle)) * speed, -sinf(RAD(angle)) * speed);

    this->angle = angle;
    this->speed = speed;
}

void UnitBase::setMove(const Vec2 &velocity) {
    this->velocity = velocity;

    angle = atan2f(velocity.y - this->velocity.y, velocity.x - this->velocity.x) * 180 / M_PI;
    speed = velocity.getLength();
}