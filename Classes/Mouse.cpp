#include "Mouse.h"

USING_NS_CC;

Vec2 Mouse::point;
bool Mouse::isTouching;
bool Mouse::isStart;
float Mouse::cursorSize = 5.f;

bool Mouse::isDown() {
    return Mouse::isTouching;
}

Vec2 &Mouse::getPoint() {
    return Mouse::point;
}

bool Mouse::onTouchBegan(Touch* touch, Event* event) {
    Mouse::isTouching = true;
    Mouse::isStart = true;
    Mouse::point = touch->getLocation();

    return true;
}

void Mouse::onTouchMoved(Touch* touch, Event* event) {
    Mouse::isStart = false;
    Mouse::point = touch->getLocation();
}

void Mouse::onTouchEnded(Touch* touch, Event* event) {
    Mouse::isTouching = false;
    Mouse::isStart = false;
    Mouse::point = touch->getLocation();
}

void Mouse::onTouchCancelled(Touch* touch, Event* event) {
    Mouse::isTouching = false;
    Mouse::isStart = false;
    Mouse::point = touch->getLocation();
}

float Mouse::getSize() {
    return Mouse::cursorSize;
}