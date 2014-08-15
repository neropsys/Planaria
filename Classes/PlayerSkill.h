#include "UI.h"
#include "cocos2d.h"

class roseKnife : public QuickSlot {
public:
    roseKnife();
    ~roseKnife();

    static roseKnife *create();
protected:
    virtual void skillSet();

    virtual void Render();
};