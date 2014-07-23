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

    ret->position.setPoint(x, y);
    ret->angle = angle;

    plas.pushBack(ret);

    ret->Init();

    return ret;
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
    Size screen = Director::getInstance()->getVisibleSize();

    setPlanariaZone(screen.height, 0, 0, screen.width);

    extendZone(-15, -15, -15, -15);

    velocity = Vec2(0, 0);
    tailEx = getNext() * 1000;

    log("%d", tailEx);

    plHead = DrawNode::create();
    plBody = DrawNode::create();

    layer->addChild(plHead);
    layer->addChild(plBody);

    for (int i = 0; i < tailSegments; i++) {
        plTail.push_back(new Vec2(position));
    }

    if (velocity.isZero()) {
        velocity.setPoint(cosf(RAD(angle)), -sinf(RAD(angle)));
        velocity.setLength(maxSpeed);


        log("%f, %f", velocity.x, velocity.y);

        //log("%f, %f", velocity.x, velocity.y);
    }
}

float Planaria::getNext() {
    return (float)rand() / RAND_MAX;
}

void Planaria::Run() {
    moveBody();
}

void Planaria::moveBody() {
    Vec2 pre = position + velocity;
}

void Planaria::calulateTail() {
    float speed = velocity.getLength();
    float pieceLength = 2 + speed / 4;
    Vec2 lastVel = -velocity;
    Vec2 pt = position;
    
    // 꼬리를 휘두르는 정도를 결정함
    float rotateAngle = 45;

    int i = 0;

    for (auto segment : plTail) {
        Vec2 pos = Vec2(segment->x, segment->y);
        Vec2 oVector = pos - pt;
        Vec2 rotatedVec = lastVel;

        tailEx += speed * 10;
        rotatedVec.rotate(Vec2(0 , 0), rotateAngle);
        rotatedVec.normalize();
        rotatedVec.setLength(-sinf((tailEx + i * 5) / 300) * 0.6);

        pt += lastVel.getNormalized() * pieceLength + rotatedVec;
        //pt += lastVel.getNormalized() * pieceLength;

        //pt += lastVel.getNormalized() * 5;

        lastVel = oVector;

        segment->setPoint(pt.x, pt.y);

        //log("%f %f", segment->x, segment->y);
        //log("%f %f", pt.x, pt.y);

        i++;
    }
}

Vec2 Planaria::align() {
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
        steer /= count;
    }

    if (!steer.isZero()) {
        steer.setLength(maxSpeed);
        steer -= position;
        steer.setLength(min(steer.getLength(), maxForce));
    }

    return steer;
}

void Planaria::Render() {
    renderTail();
    renderHead();
}

void Planaria::renderHead() {
    Vec2 pt[3];
    float ptAngle = 0;

    for (int i = 0; i < 3; i++) {
        pt[i] = Vec2(cosf(RAD(ptAngle)) * 10, sinf(RAD(ptAngle)) * 10);
        ptAngle += 120;
    }

    plHead->clear();

    plHead->setScale(1.0f);
    plHead->setPosition(position);
    plHead->setRotation(angle);

    plHead->drawTriangle(pt[0], pt[1], pt[2], Color4F(1.0f, 1.0f, 1.0f, 1.0f));
}

void Planaria::renderTail() {
    calulateTail();

    plBody->clear();

    for (auto segment : plTail) {
        Vec2 pos = Vec2(segment->x, segment->y);

        plBody->drawDot(pos, 1, Color4F(1, 1, 1, 1));
        //log("%f, %f", segment.x, segment.y);
    }
}

void Planaria::Coll() {
}

void Planaria::Dead() {
}

void Planaria::setMove(float angle, float speed) {
    velocity.setPoint(cosf(RAD(angle)) * speed, -sinf(RAD(angle)) * speed);

    this->angle = angle;
}

void Planaria::setMove(const Vec2 &velocity) {
    this->velocity = velocity;

    angle = atan2f(velocity.y - this->velocity.y, velocity.x - this->velocity.x) * 180 / M_PI;
}

void Planaria::setPlanariaZone(float top, float bottom, float left, float right) {
}

void Planaria::extendZone(float top, float bottom, float left, float right) {
}

Vec4 Planaria::getPlanariaZone() {
    return plZone;
}