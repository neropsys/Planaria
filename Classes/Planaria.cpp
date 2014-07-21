#include "Planaria.h"
#include <cmath>

Vector<Planaria *> Planaria::plas;
Layer *Planaria::layer;

Planaria::Planaria() {
}

Planaria::Planaria(Vector<Planaria *> plas) {
}

Planaria::~Planaria() {
}

void Planaria::Mainloop() {
    for (auto child : plas) {
        child->Run();
    }

    for (auto child : plas) {
        child->Dead();
    }

    for (auto child : plas) {
        child->Render();
    }
}

// static method
void Planaria::Initialize(Layer *parent) {
    layer = parent;
}

// each object's method
void Planaria::Init() {
    plHead = DrawNode::create();

    layer->addChild(plHead);

    Vec2 pt[3];

    for (int i = 0; i < 3; i++) {
        pt[i] = Vec2(cosf(angle * M_PI / 180) * 20, sinf(angle * M_PI / 180) * 20);
        angle += 120;
    }

    plHead->drawTriangle(pt[2], pt[1], pt[0], Color4F(1.0f, 1.0f, 1.0f, 1.0f));
    plHead->setScale(1.0f);
}

void Planaria::Run() {
    x += 0.5f; y += 0.5f;
}

void Planaria::Render() {
    auto headPos = plHead->getPosition();
    headPos.setPoint(x, y);

    plHead->setPosition(headPos);
    plHead->setRotation(angle);
}

void Planaria::Coll() {
}

void Planaria::Dead() {
}

Planaria *Planaria::create() {
    return create(0, 0, 0);
}

Planaria *Planaria::create(float x, float y, float angle) {
    Planaria *ret = new Planaria();

    if (ret)
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    ret->x = x;
    ret->y = y;
    ret->angle = angle;

    plas.pushBack(ret);

    ret->Init();

    return ret;
}