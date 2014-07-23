#include "cocos2d.h"
#include <cmath>
#include <iostream>

#define RAD(angle) angle * M_PI / 180

using namespace std;

class Planaria : public cocos2d::Node {

public:
    Planaria();

    virtual ~Planaria();

    static Planaria *create();
    static Planaria *create(float x, float y, float angle);
    float getNext();

    static void Initialize(cocos2d::Layer *);
    static void Mainloop();
    static void Finalize();

    void setMove(float angle, float speed);
    void setMove(const cocos2d::Vec2&);

    void setPlanariaZone(float top, float bottom, float left, float right);
    Vec4 getPlanariaZone();
    void extendZone(float top, float bottom, float left, float right);

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

    void renderHead();
    void renderTail();

    void createTail();

    virtual void moveBody();

    cocos2d::Vec2 align();
    void flock();
    void calulateTail();

    cocos2d::DrawNode *plHead, *plBody;

    vector<cocos2d::Vec2 *> plTail;
    int tailSegments = 10, tailEx = 0;

    cocos2d::Vec2 position, velocity;
    float angle = 0.f;
    float maxSpeed = 20.f, maxForce = 0.5f;

    PlanariaBox plZone;
};

class PlanariaBox {
public:
    float left;
    float top;
    float right;
    float bottom;
protected:
};