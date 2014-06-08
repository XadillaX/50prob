#include "AppDelegate.h"
#include "CMainLayer.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("50 Problems");
        director->setOpenGLView(glview);
    }

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);

    auto designSize = Size(320, 480);
    glview->setFrameSize(320, 480);
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::NO_BORDER);

    auto scene = Scene::create();
    auto layer = new MainLayer();

    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
