#include "cocos2d.h"
#include <cmath>

class Planaria : public cocos2d::Node {

public:
    Planaria();

    virtual ~Planaria();

    static Planaria *create();
    static Planaria *create(float x, float y, float angle);

    static void Initialize(cocos2d::Layer *);
    static void Mainloop();
    static void Finalize();

protected:
    static cocos2d::Vector<Planaria *> plas;
    static cocos2d::Vector<Planaria *> newPlas;
    static cocos2d::Vector<Planaria *> deadPlas;

    static cocos2d::Layer *layer;

    void Init();
    void Run();
    void Render();
    void Coll();
    void Dead();

    virtual void moveBody();

    cocos2d::DrawNode *plHead;

    cocos2d::Vec2 position;
    float angle = 0.f;
    float velocity = 0.f, vx = 0.f, vy = 0.f;
};