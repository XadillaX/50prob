#include "CItemSprite.h"
#include "Global.h"
#include "cstdio"
#include "cstdlib"
using namespace cocos2d;

Point CItemSprite::coor[9] = {
    Point(480.0 / 2.0f, 640.0 - 7.0f),
    Point(480.0 / 2.0f, 640.0 - 5.0f),
    Point(480.0 / 2.0f, 640.0 - 58.0f),
    Point(480.0 / 2.0f, 640.0 - 111.0f),
    Point(480.0 / 2.0f, 640.0 - 164.0f),
    Point(480.0 / 2.0f, 640.0 - 217.0f),

    Point(-100, 640.0 - 217.0f),
    Point(480.0 / 2.0f, -38.0f),
    Point(480.0 + 100.0f, 640.0 - 217.0f),
};

CItemSprite::CItemSprite() :
    aniTimer(0.0f),
    currentPosIndex(0)
{
}

CItemSprite::~CItemSprite()
{
}

void CItemSprite::setOpacity(GLubyte opacity)
{
    Sprite::setOpacity(opacity);
    text->setOpacity(opacity);
}

void CItemSprite::setColor(const Color3B& color)
{
    Sprite::setColor(color);
    text->setColor(color);
}

void CItemSprite::setCurrentPosition(int idx)
{
    if(idx >= 0 && idx < 9)
    {
        currentPosIndex = idx;
        currentPos = CItemSprite::coor[idx];
        this->setPosition(currentPos);

        // 透明度
        this->setOpacity((idx / 5.0) * 255);
    }
}

void CItemSprite::setNextPosition(int idx)
{
    if(idx >= 0 && idx < 9)
    {
        nextPos = CItemSprite::coor[idx];
    }
}

void CItemSprite::updatePositionAndTransparent(float totalDeltaTime)
{
    float percent = totalDeltaTime / MAX_DROP_TIMER;
    Point deltaPosition = nextPos - currentPos;
    deltaPosition *= percent;

    this->setPosition(currentPos + deltaPosition);
}

bool CItemSprite::init()
{
    // 载入纹理
    if(!Sprite::initWithFile("frame.png"))
    {
        return false;
    }

    a = rand() % 10;
    b = rand() % 10;
    sum = a + b;

    // 字
    char temp[10];
    sprintf(temp, "%d + %d =", a, b);
    text = LabelTTF::create(temp, "Optima", 24);

    // 排版
    Rect size = this->getTextureRect();
    Size textSize = text->getContentSize();

    this->addChild(text, 1);
    text->setPositionX(size.getMaxX() / 2.0f);
    text->setPositionY(size.getMaxY() / 2.0f);

    this->setColor(Color3B(0, 0, 0));

    // 位置呢
    setCurrentPosition(0);
    setNextPosition(1);

    return true;
}

TouchAction CItemSprite::rightAction()
{
    if(sum < 10) return TOA_LEFT;
    if(sum == 10) return TOA_DOWN;
    return TOA_RIGHT;
}
