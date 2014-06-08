#include "C50ProbApplication.h"
#include "CMainScene.h"
#include "cstdlib"
#include "cstdio"
using namespace cocos2d;

C50ProbApplication::C50ProbApplication(void)
{
}

C50ProbApplication::~C50ProbApplication(void)
{
}

bool C50ProbApplication::applicationDidFinishLaunching()
{
    // �������
    srand(time(NULL));

    // ��ȡ����
    director = Director::getInstance();

    // ��ȡ/���� OpenGL
    auto glView = director->getOpenGLView();
    if(!glView)
    {
        glView = GLView::create("Fifty Problems!");
        director->setOpenGLView(glView);
    }
    //director->setDisplayStats(true);
    director->setAnimationInterval(1.0f / 60.0f);

    //glView->setFrameSize(gameScreenSize.width, gameScreenSize.height);
    glView->setDesignResolutionSize(gameScreenSize.width, gameScreenSize.height, ResolutionPolicy::NO_BORDER);

    CMainScene* scene = CMainScene::create();
    scene->run();

    return true;
}

void C50ProbApplication::applicationDidEnterBackground()
{
}

void C50ProbApplication::applicationWillEnterForeground()
{
}
