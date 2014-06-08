#ifndef __CITEMSPRITE_H__
#define __CITEMSPRITE_H__
#pragma once
#include "cocos2d.h"

#define MAX_DROP_TIMER              (0.2f)

enum TouchAction
{
    TOA_NONE                        = 0,
    TOA_LEFT                        = 1,
    TOA_DOWN,
    TOA_RIGHT
};

class CItemSprite : public cocos2d::Sprite
{
public:
    CItemSprite();
    virtual ~CItemSprite();

    virtual bool                    init();

    CREATE_FUNC(CItemSprite);

    // 五个显示位置
    static cocos2d::Point           coor[9];

    // 设置坐标
    void                            setCurrentPosition(int idx);
    void                            setNextPosition(int idx);

    // 正确的动作（左中右）
    TouchAction                     rightAction();

    void                            updatePositionAndTransparent(float totalDeltaTime);

private:
    int                             a;
    int                             b;
    int                             sum;

    cocos2d::Point                  currentPos;
    cocos2d::Point                  nextPos;

    // 当下动画时间
    float                           aniTimer;
};

#endif
