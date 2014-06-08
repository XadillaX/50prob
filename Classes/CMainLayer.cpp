#include "CMainLayer.h"
using namespace cocos2d;

MainLayer::MainLayer(void)
{
}

MainLayer::~MainLayer(void)
{
}

bool MainLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }

    return true;
}
