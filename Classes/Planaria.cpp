#include "Planaria.h"

Planaria::Planaria() {
}

Planaria *Planaria::create() {
    Planaria *obj = new Planaria();

    boids.push_back(obj);

    return obj;
}

void Planaria::Mainloop(float t) {

}