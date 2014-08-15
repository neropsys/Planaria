#include "PlanariaUnits.h"

USING_NS_CC;

NormalPlanaria::NormalPlanaria() {
}

NormalPlanaria::~NormalPlanaria() {
}

NormalPlanaria *NormalPlanaria::create() {
    NormalPlanaria *ret = new NormalPlanaria();

    if (ret)
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    UnitBase::newUnit.pushBack(ret);

    return ret;
}

/////////////////////

RainbowPlanaria::RainbowPlanaria() {

}

RainbowPlanaria::~RainbowPlanaria() {

}

RainbowPlanaria *RainbowPlanaria::create() {
    RainbowPlanaria *ret = new RainbowPlanaria();

    if (ret)
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    UnitBase::newUnit.pushBack(ret);

    return ret;
}

void RainbowPlanaria::cutBody(const Vec2 &pos) {
    if (bodyLength < 80 || isHurted) {
        return;
    }

    int crashedSegment = getCrashedSegment(pos);
    log("%d", crashedSegment);
    Vec2 *crashedPos = plTail[crashedSegment];
    float dividedLength = crashedSegment * getSegmentLength();

    //auto pl = RainbowPlanaria::create();
    auto pl2 = RainbowPlanaria::create();

    pl2->position.setPoint(crashedPos->x, crashedPos->y);
    pl2->setMove(angle - 20 + getNext() * 40, 0.5);
    pl2->bodyLength = bodyLength - dividedLength;

    pl2->isHurted = true;

    this->isHurted = true;
    this->bodyLength = dividedLength;
    isHurted = true;

    //Die();
}

void RainbowPlanaria::Run() {
    Planaria::Run();

    this->bodyColor = Color4F(getNext(), getNext(), getNext(), 1.f);

    //log("ew");
}

//////////////////////

ExtendedPlanaria::ExtendedPlanaria() {

}

ExtendedPlanaria::~ExtendedPlanaria() {

}

ExtendedPlanaria *ExtendedPlanaria::create() {
    ExtendedPlanaria *ret = new ExtendedPlanaria();

    if (ret)
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    UnitBase::newUnit.pushBack(ret);

    return ret;
}

void ExtendedPlanaria::Init() {
    this->bodyLength = 200.f;
    this->bodyMaxLength = this->bodyLength;

    Planaria::Init();
}