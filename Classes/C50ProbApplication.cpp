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
    // 随机种子
    srand(time(NULL));

    // 获取导演
    director = Director::getInstance();

    // 获取/设置 OpenGL
    auto glView = director->getOpenGLView();
    if(!glView)
    {
        glView = GLView::create("Fifty Problems!");
        director->setOpenGLView(glView);
    }
    //director->setDisplayStats(true);
    director->setAnimationInterval(1.0f / 60.0f);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    glView->setFrameSize(gameScreenSize.width, gameScreenSize.height);
#endif
    glView->setDesignResolutionSize(gameScreenSize.width, gameScreenSize.height, ResolutionPolicy::NO_BORDER);

    CMainScene* scene = CMainScene::create();
    scene->run();

    return true;
}

void C50ProbApplication::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
}

void C50ProbApplication::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
}
