#include "CMainScene.h"
#include "CItemLayer.h"
using namespace cocos2d;

CMainScene::CMainScene(void) :
    lastBackTime(-1)
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

    // ¼üÅÌÕìÌý
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(CMainScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    return true;
}

void CMainScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        if(lastBackTime == -1)
        {
            lastBackTime = getMillionSeconds();
        }
        else
        {
            long temp = getMillionSeconds();
            if(temp - lastBackTime < 500)
            {
                // ÍË³ö
                Director::getInstance()->end();

                #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                exit(0);
                #endif
            }
            else
            {
                lastBackTime = temp;
            }
        }
    }
}

void CMainScene::run()
{
    scene->addChild(this);
    director->runWithScene(scene);
}
