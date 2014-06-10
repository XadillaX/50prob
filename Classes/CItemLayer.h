#ifndef __CITEMLAYER_H__
#define __CITEMLAYER_H__
#pragma once
#include "cocos2d.h"
#include "CItemSprite.h"
#include <list>
#include <vector>

class CItemLayer : public cocos2d::Layer
{
public:
    CItemLayer();
    virtual ~CItemLayer();

    virtual bool                    init();
    virtual void                    startNewGame();
    void                            endGame();

    virtual void                    onEnter();

    virtual bool                    onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void                    onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void                            onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    virtual void                    update(float delta);
    void                            updateSmileAndCry();

    bool                            isDropping();

    CREATE_FUNC(CItemLayer);

private:
    std::list<CItemSprite*>         sprites;
    std::list<TouchAction>          actions;

    // �Ƿ����ڵ���
    float                           droppingTimer;
    bool                            dropping;
    bool                            playing;

    // ��ʱ��ʼ
    float                           playTime;
    bool                            isCalculatingTime;

    // �����ж�
    cocos2d::Point                  startTouchPos;
    cocos2d::Point                  endTouchPos;

    // ��ʱ
    cocos2d::LabelTTF*              timeLabel;
    cocos2d::LabelTTF*              smileAndCry;
    cocos2d::LabelTTF*              winLabel;

    int                             perCount[2];

    float                           bestTime;
    cocos2d::LabelTTF*              bestTimeLabel;
};

#endif
