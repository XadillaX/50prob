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

    virtual void                    onEnter();

    virtual bool                    onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void                    onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

    virtual void                    update(float delta);

    bool                            isDropping();

    CREATE_FUNC(CItemLayer);

private:
    std::list<CItemSprite*>         sprites;
    std::list<TouchAction>          actions;

    // 是否正在掉落
    float                           droppingTimer;
    bool                            dropping;
    bool                            playing;

    // 手势判断
    cocos2d::Point                  startTouchPos;
    cocos2d::Point                  endTouchPos;
};

#endif
