#include "cocos2d.h"
#include <cmath>
#include <iostream>

#define RAD(angle) angle * M_PI / 180

using namespace std;

class PlanariaBox {
public:

    PlanariaBox();
    PlanariaBox(float left, float top, float right, float bottom);

    ~PlanariaBox();

    float left;
    float top;
    float right;
    float bottom;
protected:
};

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
    void setPlanariaZone(const PlanariaBox&);
    void extendZone(float top, float bottom, float left, float right);
    void extendZone(const PlanariaBox&);
    PlanariaBox getPlanariaZone();

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
    int tailSegments = 20, tailEx = 0;

    cocos2d::Vec2 position, velocity;
    float angle = 0.f, speed = 0.f;
    float exAngle = 0.f, exSpeed = 0.f;
    float maxSpeed = 6.f, minSpeed = 2.f;
    float bodyLength = 120.f, bodySize = 4.5f;

    int t = 0;

    PlanariaBox plZone;
};