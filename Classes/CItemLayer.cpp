#include "CItemLayer.h"
#include "Global.h"
using namespace cocos2d;

CItemLayer::CItemLayer() :
    dropping(false),
    playing(false),
    droppingTimer(0.0f)
{
}

CItemLayer::~CItemLayer()
{
}

bool CItemLayer::isDropping()
{
    return dropping;
}

bool CItemLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }

    // 需要帧函数
    scheduleUpdate();

    // 初始化...
    startNewGame();
}

void CItemLayer::onEnter()
{
    Layer::onEnter();

    // 手势侦听
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(CItemLayer::onTouchBegan, this);
    //listener->onTouchMoved = CC_CALLBACK_2(Paddle::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(CItemLayer::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool CItemLayer::onTouchBegan(Touch* touch, Event* event)
{
    if(!playing) return false;

    startTouchPos = touch->getLocation();
    return true;
}

void CItemLayer::update(float delta)
{
    Layer::update(delta);

    // 正在掉落
    if(dropping)
    {
        droppingTimer += delta;

        int j = 0;
        for(std::list<CItemSprite*>::iterator it = sprites.begin(); j < 6 && it != sprites.end(); it++, j++)
        {
            (*it)->updatePositionAndTransparent(droppingTimer);
        }

        if(droppingTimer >= MAX_DROP_TIMER)
        {
            droppingTimer = 0.0f;
            dropping = false;
            CItemSprite* sprite = sprites.front();
            sprites.pop_front();
            this->removeChild(sprite, true);

            //for(
        }
    }
    else
    if(playing && !actions.empty())
    {
        //MessageBox("a", "b");
        int j = 0;
        for(std::list<CItemSprite*>::iterator it = sprites.begin(); j < 6 && it != sprites.end(); it++, j++)
        {
            CItemSprite* sprite = *it;
            if(j == 0)
            {
                sprite->setNextPosition(5 + (int)(actions.front()));
            }

            if(j == 5)
            {
                this->addChild(sprite);
            }
        }

        actions.pop_front();

        dropping = true;
    }
}

void CItemLayer::onTouchEnded(Touch* touch, Event* event)
{
    //Layer::onTouchEnded(touch, event);
    if(!playing) return;

    endTouchPos = touch->getLocation();

    // 判断方向
    auto delta = endTouchPos - startTouchPos;
    if(delta.length() < 20) return;

    // 横向
    if(fabs(delta.x) > fabs(delta.y))
    {
        if(fabs(delta.y) / fabs(delta.x) > 1.0f / 5.0f) return;

        if(delta.x < 0)
        {
            // 加入左边
            actions.push_back(TOA_LEFT);
        }
        else
        if(delta.x > 0)
        {
            // 加入右边
            actions.push_back(TOA_RIGHT);
        }
    }
    // 纵向
    else
    {
        if(fabs(delta.x) / fabs(delta.y) > 1.0f / 5.0f) return;

        if(delta.y < 0)
        {
            // 加入下边
            actions.push_back(TOA_DOWN);
        }
    }
}

void CItemLayer::startNewGame()
{
    dropping = false;

    // 清除上一关卡
    while(!sprites.empty())
    {
        sprites.pop_front();
    }
    while(!actions.empty())
    {
        actions.pop_front();
    }

    // 新建 50 个方块
    for(int i = 0; i < 50; i++)
    {
        //CItemSprite* sprite = CItemSprite::create();
        //sprite->setAnchorPoint(Size(50, 19));
        CItemSprite* sprite = new CItemSprite();
        sprite->init();
        sprites.push_back(sprite);

        if(i < 5)
        {
            // 如果是前五个，则事先设定好位置
            sprite->setCurrentPosition(5 - i);
            sprite->setNextPosition(5 - i + 1);

            // 加入儿子
            this->addChild(sprite);
        }
    }

    playing = true;
}
