#include "cocos2d.h"
#include "UnitBase.h"
#include "Planaria.h"
#include "UI.h"
#pragma once

class Poison : public UnitBase {
public:
    CREATE_FUNC3(Poison);

    static Poison *create(float time, float size);

    void setSize(float size);
    float getSize() { return cloudRadius; };

    void setTime(float time);
    float getTime() { return timeLimit; };

    static cocos2d::Vector<Poison *> group;

    void setOver();

protected:

    virtual void Init();
    virtual void Run();
    virtual void Dead();

    float cloudRadius = 50.f;

    int t = 0;
    float timeLimit = 0;
    bool isTimeLimited = false;
    bool isOver = false;

    float fadeOut = 0.f;

    cocos2d::SpriteBatchNode *posDisp;
    cocos2d::Sprite *cloud;
};

class PoisonExEffect : public UnitBase {
public:
    CREATE_FUNC3(PoisonExEffect);

    static PoisonExEffect *create(float time, float size);

    void setSize(float size);
    float getSize() { return cloudRadius; };

    void setTime(float time);
    float getTime() { return timeLimit; };

    void setOver();

protected:

    virtual void Init();
    virtual void Run();
    virtual void Dead();

    float cloudRadius = 50.f;

    int t = 0;
    float timeLimit = 0;
    bool isTimeLimited = false;
    bool isOver = false;

    float fadeOut = 0.f;

    cocos2d::SpriteBatchNode *posDisp;
    cocos2d::Sprite *cloud;
};