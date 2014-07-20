#include "Planaria.h"

Vector<Planaria *> Planaria::plas;

Planaria::Planaria() {
}

Planaria::Planaria(Vector<Planaria *> plas) {
}

Planaria::~Planaria() {
}

void Planaria::Mainloop() {
}

void Planaria::Init(Layer *layer) {
}

void Planaria::Run() {
}

void Planaria::Coll() {
}

void Planaria::Dead() {
}

Planaria *Planaria::create(Vector<Planaria *> plas) {
    Planaria *ret = new Planaria();

    if (ret)
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}