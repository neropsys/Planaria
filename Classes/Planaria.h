#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Planaria : public cocos2d::Node {

public:
    Planaria();

    Planaria(Vector<Planaria *> plas);

    virtual ~Planaria();

    static Planaria *create(Vector<Planaria *> plas);

    static void Mainloop();

protected:
    static Vector<Planaria *> plas;

    void Init(Layer *);
    void Run();
    void Coll();
    void Dead();
};