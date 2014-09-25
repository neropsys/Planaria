#include "Poison.h"

USING_NS_CC;

Vector<Poison *> Poison::group;

Poison *Poison::create(float time, float size) {
    auto obj = Poison::create();

    obj->setTime(time);
    obj->setSize(size);

    return obj;
}

void Poison::Init() {
    UnitBase::Init();

    posDisp = SpriteBatchNode::create("sprite.png");

    UnitBase::layer->addChild(posDisp, Z_UNIT);

    cloud = Sprite::createWithSpriteFrameName("poison.png");

    cloud->setRotation(rand() / RAND_MAX);

    posDisp->addChild(cloud);

    Poison::group.pushBack(this);
}

void Poison::Run() {
    UnitBase::Run();

    posDisp->setPosition(this->getPosition());

    if (isOver) {
        fadeOut -= 0.02f;
        cloudRadius *= 1.005;

        if (fadeOut < 0) {
            fadeOut = 0;
            Die();
        }
    }
    else {
        if (fadeOut < 1) {
            fadeOut += 0.05f;
            
            if (fadeOut > 1) {
                fadeOut = 1;
            }
        }
        else {
            for (auto child : Planaria::Plas) {
                if (child->isCrash(this->getPosition(), cloudRadius)) {
                    int c = 0;

                    for (auto segment : child->getTail()) {
                        if (c % 2 == 0) {
                            auto pos = PoisonExEffect::create(50, 10);

                            pos->setPosition(segment->x, segment->y);
                        }

                        c++;
                    }

                    child->Die();
                    break;
                }
            }
        }
    }

    if (isTimeLimited) {
        if (timeLimit > 0) {
            timeLimit -= 1.f;
        }
        
        if (timeLimit < 0) {
            timeLimit = 0;
        }
            
        if (timeLimit == 0) {
            isOver = true;
        }
    }

    cloud->setScale(cloudRadius / 65 + 0.05 * sinf(t / 10.f));
    cloud->setOpacity(255 * fadeOut);

    t++;
}

void Poison::Dead() {
    posDisp->removeAllChildren();

    UnitBase::layer->removeChild(posDisp);

    Poison::group.eraseObject(this);
}

void Poison::setTime(float time) {
    timeLimit = time;

    isTimeLimited = true;
}

void Poison::setSize(float size) {
    cloudRadius = size;
}

void Poison::setOver() {
    isOver = true;
}


PoisonExEffect *PoisonExEffect::create(float time, float size) {
    auto obj = PoisonExEffect::create();

    obj->setTime(time);
    obj->setSize(size);

    return obj;
}

void PoisonExEffect::Init() {
    UnitBase::Init();

    posDisp = SpriteBatchNode::create("sprite.png");

    UnitBase::layer->addChild(posDisp, Z_UNIT);

    cloud = Sprite::createWithSpriteFrameName("poison.png");

    cloud->setRotation(rand() / RAND_MAX);

    posDisp->setBlendFunc(GL_BLEND_SCREENMODE);

    posDisp->addChild(cloud);
}

void PoisonExEffect::Run() {
    UnitBase::Run();

    posDisp->setPosition(this->getPosition());

    if (isOver) {
        fadeOut -= 0.05f;
        cloudRadius *= 1.05f;

        if (fadeOut < 0) {
            fadeOut = 0;
            Die();
        }
    }
    else {
        if (fadeOut < 1) {
            fadeOut += 0.1f;

            if (fadeOut > 1) {
                fadeOut = 1;

                isOver = true;
            }
        }
    }

    if (isTimeLimited) {
        if (timeLimit > 0) {
            timeLimit -= 1.f;
        }

        if (timeLimit < 0) {
            timeLimit = 0;
        }

        if (timeLimit == 0) {
            isOver = true;
        }
    }

    cloud->setScale(cloudRadius / 65);
    cloud->setOpacity(255 * fadeOut);

    t++;
}

void PoisonExEffect::Dead() {
    posDisp->removeAllChildren();

    UnitBase::layer->removeChild(posDisp);
}

void PoisonExEffect::setTime(float time) {
    timeLimit = time;

    isTimeLimited = true;
}

void PoisonExEffect::setSize(float size) {
    cloudRadius = size;
}

void PoisonExEffect::setOver() {
    isOver = true;
}