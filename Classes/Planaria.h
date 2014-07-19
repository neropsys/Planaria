#include "cocos2d.h"
#include <list>

using namespace std;

class Planaria {
public:
    Planaria();
    virtual ~Planaria();

    static Planaria *create();

    void Mainloop(float);

private:
    float x, y;
    float velocity;

    static list<Planaria *> boids;
};