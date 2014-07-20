#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Planaria : public cocos2d::Node {

public:
    Planaria();

    Planaria(Vector<Planaria *> plas);

    virtual ~Planaria();

    static Planaria *create();
    static Planaria *create(float x, float y, float angle);

    static void Initialize(Layer *);
    static void Mainloop();

protected:
    static Vector<Planaria *> plas;
    static Layer *layer;

    void Init();
    void Run();
    void Render();
    void Coll();
    void Dead();

    DrawNode *plHead, *plBody;

    float x = 0.f, y = 0.f;
    float angle = 0.f;
    float velocity = 0.f, vx = 0.f, vy = 0.f;
};