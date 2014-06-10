#ifndef __CITEMSPRITE_H__
#define __CITEMSPRITE_H__
#pragma once
#include "cocos2d.h"

#define MAX_DROP_TIMER              (0.15f)

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

    virtual void                    setOpacity(GLubyte opacity);
    virtual void                    setColor(const cocos2d::Color3B& color);

private:
    int                             a;
    int                             b;
    int                             sum;

    int                             currentPosIndex;
    cocos2d::Point                  currentPos;
    cocos2d::Point                  nextPos;

    cocos2d::LabelTTF*              text;

    // ���¶���ʱ��
    float                           aniTimer;
};

#endif
