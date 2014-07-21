#include "Planaria.h"

USING_NS_CC;

Vector<Planaria *> Planaria::plas;
Vector<Planaria *> Planaria::newPlas;
Vector<Planaria *> Planaria::deadPlas;

Layer *Planaria::layer;

Planaria::Planaria() {
}

Planaria::~Planaria() {
}

// static method
void Planaria::Initialize(Layer *parent) {
    layer = parent;
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

void Planaria::Finalize() {
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
    moveBody();
}

void Planaria::moveBody() {
    int neighborDist = 25, count = 0;
    Vec2 steer = Vec2(0, 0);

    for (auto other : plas) {
        float distance = position.getDistance(other->position);

        if (distance > 0 && distance < neighborDist) {
            steer += other->position;

            count++;
        }
    }

    if (count > 0) {
        steer = steer / count;
    }
}

void Planaria::Render() {
    plHead->setPosition(position);
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