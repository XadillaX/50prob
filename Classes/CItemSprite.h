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

    // �����ʾλ��
    static cocos2d::Point           coor[9];

    // ��������
    void                            setCurrentPosition(int idx);
    void                            setNextPosition(int idx);

    // ��ȷ�Ķ����������ң�
    TouchAction                     rightAction();

    void                            updatePositionAndTransparent(float totalDeltaTime);

private:
    int                             a;
    int                             b;
    int                             sum;

    cocos2d::Point                  currentPos;
    cocos2d::Point                  nextPos;

    // ���¶���ʱ��
    float                           aniTimer;
};

#endif
