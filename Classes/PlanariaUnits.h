#ifndef _PLANARIA_UNITS_H_
#define _PLANARIA_UNITS_H_

#include "cocos2d.h"
#include "Planaria.h"

class NormalPlanaria : public Planaria {
public:
    NormalPlanaria();
    
    ~NormalPlanaria();

    static NormalPlanaria *create();

protected:
};

class RainbowPlanaria : public Planaria {
public:
    RainbowPlanaria();
    ~RainbowPlanaria();

    static RainbowPlanaria *create();
    virtual void cutBody(const cocos2d::Vec2 &pos);
protected:

    void Run();
};

class ExtendedPlanaria : public Planaria {
public:
    ExtendedPlanaria();
    ~ExtendedPlanaria();

    static ExtendedPlanaria *create();
protected:

    void Init();
};
#endif