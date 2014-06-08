#include "CMainScene.h"
#include "CItemLayer.h"
using namespace cocos2d;

CMainScene::CMainScene(void)
{
    scene = Scene::create();
    director = Director::getInstance();
}

CMainScene::~CMainScene(void)
{
}

bool CMainScene::init()
{
    // ³õÊ¼»¯¸¸Àà
    if(!CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)))
    {
        return false;
    }

    CItemLayer* itemLayer = CItemLayer::create();
    itemLayer->setPosition(Point(0, 0));
    itemLayer->setAnchorPoint(Point(0, 0));
    itemLayer->setContentSize(Size(480, 640));

    this->addChild(itemLayer);

    return true;
}

void CMainScene::run()
{
    scene->addChild(this);
    director->runWithScene(scene);
}
