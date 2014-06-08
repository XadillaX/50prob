#ifndef __C50PROBAPPLICATION_H__
#define __C50PROBAPPLICATION_H__
#pragma once
#include "Global.h"
#include "cocos2d.h"

class C50ProbApplication : public cocos2d::Application
{
public:
    C50ProbApplication(void);
    virtual ~C50ProbApplication(void);

public:
    // 游戏运行
    virtual bool                    applicationDidFinishLaunching();

    // 游戏到后台
    virtual void                    applicationDidEnterBackground();

    // 游戏回前台
    virtual void                    applicationWillEnterForeground();

private:
    cocos2d::Director*              director;
};
#endif
