#include "Planaria.h"

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

    plHead->drawTriangle(Vec2(10, 10), Vec2(10, 20), Vec2(20, 20), Color4F(1.0f, 1.0f, 1.0f, 1.0f));
}

void Planaria::Run() {
}

void Planaria::Render() {
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