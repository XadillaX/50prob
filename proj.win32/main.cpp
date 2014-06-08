#include "main.h"
#include "C50ProbApplication.h"
using namespace cocos2d;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "vld.h"  
#endif

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    C50ProbApplication app;
    return Application::getInstance()->run();
}
