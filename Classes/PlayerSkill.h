#include "UI.h"
#include "cocos2d.h"
#include "Planaria.h"

class roseKnife : public QuickSlot {
public:
    roseKnife();
    ~roseKnife();

    static roseKnife *create();
protected:
    virtual void skillSet();

    virtual void Render();

    int t = 0;
};