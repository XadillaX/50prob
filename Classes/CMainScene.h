#ifndef __CMAINSCENE_H__
#define __CMAINSCENE_H__
#pragma once
#include "Global.h"
#include "cocos2d.h"

class CMainScene : public cocos2d::CCLayerColor
{
public:
    CMainScene(void);
    virtual ~CMainScene(void);

    void                            run();

    // �� CMainScene::create() ����
    virtual bool                    init();

    void                            onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);


    // ���ü�������ʵ��
    CREATE_FUNC(CMainScene);

private:
    cocos2d::Scene*                 scene;
    cocos2d::Director*              director;

    long                            lastBackTime;
};
#endif
