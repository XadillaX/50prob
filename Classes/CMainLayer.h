#ifndef __CMAINSCENE_H__
#define __CMAINSCENE_H__
#pragma once
#include "cocos2d.h"
class MainLayer : public cocos2d::Layer
{
public:
    MainLayer(void);
    virtual                     ~MainLayer(void);

    virtual bool                init();
};
#endif
