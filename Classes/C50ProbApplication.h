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
    // ��Ϸ����
    virtual bool                    applicationDidFinishLaunching();

    // ��Ϸ����̨
    virtual void                    applicationDidEnterBackground();

    // ��Ϸ��ǰ̨
    virtual void                    applicationWillEnterForeground();

private:
    cocos2d::Director*              director;
};
#endif
