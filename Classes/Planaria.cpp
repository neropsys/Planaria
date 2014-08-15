#include "Planaria.h"

USING_NS_CC;

Vector<Planaria *> Planaria::Plas;

Layer *Planaria::layer;

Planaria::Planaria() {
}

Planaria::~Planaria() {
}

bool Planaria::onTouchBegan(Touch* touch, Event* event) {
    Vec2 tPos = touch->getLocation();

    for (auto child : Plas) {
        if (child->isCrash(tPos, 5)) {
            child->cutBody(tPos);
        }
    }

    return true;
}

void Planaria::onTouchMoved(Touch* touch, Event* event) {
    Vec2 tPos = touch->getLocation();

    for (auto child : Plas) {
        if (child->isCrash(tPos, 5)) {
            child->cutBody(tPos);
        }
    }
}

void Planaria::onTouchEnded(Touch* touch, Event* event) {
}

void Planaria::onTouchCancelled(Touch* touch, Event* event) {
}

Planaria *Planaria::create() {
    return create(0, 0, 0, 0, 120);
}

Planaria *Planaria::create(float x, float y, float angle) {
    return create(x, y, angle, 0, 120);
}

Planaria *Planaria::create(float x, float y, float angle, float speed) {
    return create(x, y, angle, 0, 120);
}

Planaria *Planaria::create(float x, float y, float angle, float speed, float length) {
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
    ret->speed = speed;
    ret->bodyLength = length;

    UnitBase::newUnit.pushBack(ret);

    return ret;
}

void Planaria::setPosition(float x, float y) {
    this->position.x = x;
    this->position.y = y;
}

Vec2 Planaria::getPosition() {
    return position;
}

void Planaria::setAngle(float angle) {
    this->angle = angle;

    setVelocity();
}

float Planaria::getAngle() {
    return angle;
}

void Planaria::setSpeed(float speed) {
    this->speed = speed;

    setVelocity();
}

float Planaria::getSpeed() {
    return speed;
}

void Planaria::setVelocity() {
    velocity.setPoint(cosf(RAD(angle)) * speed, -sinf(RAD(angle)) * speed);
}

void Planaria::Die() {
    deadUnit.pushBack(this);
}

// static method
void Planaria::Initialize(Layer *parent) {
    layer = parent;

    Size visibleSize = Director::getInstance()->getVisibleSize();
}

void Planaria::Mainloop() {
}

void Planaria::Finalize() {
}

// each object's method
void Planaria::Init() {
    Size screen = Director::getInstance()->getVisibleSize();
    float baseMargin = 30.f;

    bodyColor = Color4F(1.f, 1.f, 1.f, 1.f);

    // this is fucking why I blame the coordinate system of cocos2dx....
    setPlanariaZone(screen.height, 0, 0, screen.width);
    extendZone(-baseMargin, baseMargin, baseMargin, -baseMargin);

    velocity = Vec2(0, 0);
    tailEx = getNext() * 1000;

    plHead = DrawNode::create();
    plBody = DrawNode::create();

    UnitBase::layer->addChild(plHead);
    UnitBase::layer->addChild(plBody);

    for (int i = 0; i < tailSegments; i++) {
        plTail.push_back(new Vec2(position));
    }

    if (velocity.isZero()) {
        setMove(angle, 1);

        //log("%f, %f", velocity.x, velocity.y);

        //log("%f, %f", velocity.x, velocity.y);
    }

    Plas.pushBack(this);

    Render();
}

float Planaria::getNext() {
    return (float)rand() / RAND_MAX;
}

void Planaria::Run() {
    //log("test");
    /*if (this->isCrash(Mouse::getPoint(), Mouse::getSize()) && Mouse::isDown()) {
        cutBody(Mouse::getPoint());
    }*/

    Recovery();

    moveBody();

    Render();

    t++;
}

void Planaria::Recovery() {
    if (bodyLength < bodyMaxLength) {
        bodyLength += 0.8f;
    }

    if (bodyLength > bodyMaxLength) {
        isHurted = false;
        bodyLength = bodyMaxLength;
    }
}

void Planaria::moveBody() {
    Vec2 pre = position + velocity;

    float reflectAngle = 140.f;

    if (pre.x < plZone.left) {
        pre.x = plZone.left;
        angle += getNext() * reflectAngle - reflectAngle / 2;
    }
    if (pre.x > plZone.right) {
        pre.x = plZone.right;
        angle += getNext() * reflectAngle - reflectAngle / 2;
    }
    if (pre.y > plZone.top) {
        pre.y = plZone.top;
        angle += getNext() * reflectAngle - reflectAngle / 2;
    }
    if (pre.y < plZone.bottom) {
        pre.y = plZone.bottom;
        angle += getNext() * reflectAngle - reflectAngle / 2;
    }

    /*Vec2 steer = align();

    if (!steer.isZero()) {
        setMove(steer);
    }*/

    // later, these is gonna be changed to display natural Planaria
    if (t % 50 == 0 && t > 0) {
        exAngle = 6 * getNext() - 3;
    }

    if (t % 70 == 0 && t > 0) {
        exSpeed = 6 * getNext() - 3;
    }
    
    speed -= exSpeed;

    if (t % 90 == 0) {
        exSpeed = 0;
    }

    float realSpeed = speed + exSpeed;

    if (realSpeed > maxSpeed) {
        realSpeed = maxSpeed;
    }
    if (realSpeed < minSpeed) {
        realSpeed = minSpeed;
    }

    setMove(angle + exAngle, realSpeed);

    position = pre;
}

float Planaria::getSegmentLength() {
    return bodyLength / tailSegments;
}

void Planaria::calulateTail() {
    float acceleration = this->speed * this->speed;
    float pieceLength = this->getSegmentLength() + speed / 3;
    Vec2 lastVel = -velocity;
    Vec2 pt = position;
    
    // 꼬리를 휘두르는 정도를 결정함 (amount of planaria's tail snap increases if this value is small)
    float rotateAngle = 40;

    // 너무 낮으면 애가 흔드는지 안흔드는지....
    if (acceleration < pieceLength) {
        acceleration = pieceLength - this->speed;
    }

    int i = 0;

    for (auto segment : plTail) {
        Vec2 pos = Vec2(segment->x, segment->y);
        Vec2 oVector = pos - pt;
        Vec2 rotatedVec = lastVel;

        tailEx += this->speed;
        rotatedVec.rotate(pos, rotateAngle);
        rotatedVec.normalize();
        rotatedVec.setLength(-sinf((tailEx + i * 2) / 300) * 0.05);

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

    for (auto other : Plas) {
        float distance = position.getDistance(other->position);

        if (distance > 0 && distance < neighborDist) {
            steer += other->velocity;

            count++;
        }
    } 

    if (count > 0) {
        steer /= count;
    }

    if (!steer.isZero()) {
        steer.setLength(speed);
        steer -= velocity;
        steer.setLength(speed);
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
    float headSize = bodySize + bodySize / 1.2;

    for (int i = 0; i < 3; i++) {
        pt[i] = Vec2(cosf(RAD(ptAngle)) * headSize, sinf(RAD(ptAngle)) * headSize);
        ptAngle += 120;
    }

    plHead->clear();

    plHead->setScale(1.0f);
    plHead->setPosition(position);
    plHead->setRotation(angle);

    plHead->drawTriangle(pt[0], pt[1], pt[2], bodyColor);
}

void Planaria::renderTail() {
    int i = 0;
    Vec2 lastPos;

    calulateTail();

    plBody->clear();

    for (auto segment : plTail) {
        Vec2 pos = Vec2(segment->x, segment->y);

        //plBody->drawDot(pos, 1, Color4F(1, 1, 1, 1));
        //log("%f, %f", segment.x, segment.y);

        if (i < tailSegments) {
            if (i > 0) {
                plBody->drawSegment(lastPos, pos, getSegmentSize(i), bodyColor);

                //tailSize -= 0.15;
            }

            lastPos = pos;
        }

        i++;
    }
}

void Planaria::Coll() {
}

void Planaria::Dead() {
    Plas.eraseObject(this, false);

    UnitBase::layer->removeChild(plHead, true);
    UnitBase::layer->removeChild(plBody, true);
    //plHead->autorelease();
    //plBody->autorelease();
}

void Planaria::setMove(float angle, float speed) {
    velocity.setPoint(cosf(RAD(angle)) * speed, -sinf(RAD(angle)) * speed);

    this->angle = angle;
    this->speed = speed;
}

void Planaria::setMove(const Vec2 &velocity) {
    this->velocity = velocity;

    angle = atan2f(velocity.y - this->velocity.y, velocity.x - this->velocity.x) * 180 / M_PI;
    speed = velocity.getLength();
}

void Planaria::setPlanariaZone(float top, float bottom, float left, float right) {
    plZone.top = top;
    plZone.bottom = bottom;
    plZone.left = left;
    plZone.right = right;
}

void Planaria::setPlanariaZone(const PlanariaBox &box) {
    plZone.top = box.top;
    plZone.bottom = box.bottom;
    plZone.left = box.left;
    plZone.right = box.right;
}

void Planaria::extendZone(float top, float bottom, float left, float right) {
    plZone.top += top;
    plZone.bottom += bottom;
    plZone.left += left;
    plZone.right += right;
}

void Planaria::extendZone(const PlanariaBox &box) {
    plZone.top += box.top;
    plZone.bottom += box.bottom;
    plZone.left += box.left;
    plZone.right += box.right;
}

bool Planaria::isCrash(const Vec2 &pt, float radius) {
    return isCrash(pt.x, pt.y, radius);
}

bool Planaria::isCrash(float x, float y, float radius) {
    int i = 0;

    for (auto segment : plTail) {
        float distX = x - segment->x, distY = y - segment->y;
        float size = getSegmentSize(i), realSize = size + radius;

        if ((distX * distX + distY * distY) < (realSize * realSize)) {
            return true;
        }

        i++;
    }

    return false;
}

int Planaria::getCrashedSegment(const Vec2 &pt) {
    return getCrashedSegment(pt.x, pt.y, Mouse::getSize());
}

int Planaria::getCrashedSegment(float x, float y, float radius) {
    int i = 0;
    int nearestSegment = -1;
    float minDist = -1;

    for (auto segment : plTail) {
        float distX = x - segment->x, distY = y - segment->y;
        float dist = distX * distX + distY * distY;
        float size = getSegmentSize(i), realSize = size + radius;

        if (dist < realSize * realSize) {
            if (minDist < 0) {
                minDist = dist;
            }

            if (dist <= minDist) {
                minDist = dist;
                nearestSegment = i;
            }
        }

        i++;
    }

    return nearestSegment;
}

inline float Planaria::getSegmentSize(int n) {
    return bodySize + bodySize * sinf((float)n * 3 / tailSegments);
}

void Planaria::cutBody(const Vec2 &pos) {
    if (bodyLength < 80 || isHurted) {
        return;
    }

    int crashedSegment = getCrashedSegment(pos);
    log("%d", crashedSegment);
    Vec2 *crashedPos = plTail[crashedSegment];
    float dividedLength = crashedSegment * getSegmentLength();

    auto pl2 = Planaria::create(crashedPos->x, crashedPos->y, angle - 20 + getNext() * 40, 0.5, bodyLength - dividedLength);
    this->bodyLength = dividedLength;
    this->isHurted = true;

    //pl->isHurted = true;
    pl2->isHurted = true;

    isHurted = true;
}

PlanariaBox Planaria::getPlanariaZone() {
    return plZone;
}

////////////////////////////////////////////////////

PlanariaBox::PlanariaBox() {
    left = 0;
    top = 0;
    right = 0;
    bottom = 0;
}

PlanariaBox::PlanariaBox(float left, float top, float right, float bottom) {
    this->left = left;
    this->top = top;
    this->right = right;
    this->bottom = bottom;
}

PlanariaBox::~PlanariaBox() {
}