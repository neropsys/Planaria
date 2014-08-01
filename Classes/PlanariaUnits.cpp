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

    newPlas.pushBack(ret);

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

    newPlas.pushBack(ret);

    return ret;
}

void RainbowPlanaria::Run() {
    Planaria::Run();

    this->bodyColor = Color4F(getNext(), getNext(), getNext(), 1.f);

    log("ew");
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

    newPlas.pushBack(ret);

    return ret;
}

void ExtendedPlanaria::Init() {
    this->bodyLength = 200.f;

    Planaria::Init();
}