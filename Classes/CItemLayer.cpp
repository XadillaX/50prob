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

    // ��Ҫ֡����
    scheduleUpdate();

    // ��ʼ��...
    startNewGame();
}

void CItemLayer::onEnter()
{
    Layer::onEnter();

    // ��������
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

    // ���ڵ���
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

    // �жϷ���
    auto delta = endTouchPos - startTouchPos;
    if(delta.length() < 20) return;

    // ����
    if(fabs(delta.x) > fabs(delta.y))
    {
        if(fabs(delta.y) / fabs(delta.x) > 1.0f / 5.0f) return;

        if(delta.x < 0)
        {
            // �������
            actions.push_back(TOA_LEFT);
        }
        else
        if(delta.x > 0)
        {
            // �����ұ�
            actions.push_back(TOA_RIGHT);
        }
    }
    // ����
    else
    {
        if(fabs(delta.x) / fabs(delta.y) > 1.0f / 5.0f) return;

        if(delta.y < 0)
        {
            // �����±�
            actions.push_back(TOA_DOWN);
        }
    }
}

void CItemLayer::startNewGame()
{
    dropping = false;

    // �����һ�ؿ�
    while(!sprites.empty())
    {
        sprites.pop_front();
    }
    while(!actions.empty())
    {
        actions.pop_front();
    }

    // �½� 50 ������
    for(int i = 0; i < 50; i++)
    {
        //CItemSprite* sprite = CItemSprite::create();
        //sprite->setAnchorPoint(Size(50, 19));
        CItemSprite* sprite = new CItemSprite();
        sprite->init();
        sprites.push_back(sprite);

        if(i < 5)
        {
            // �����ǰ������������趨��λ��
            sprite->setCurrentPosition(5 - i);
            sprite->setNextPosition(5 - i + 1);

            // �������
            this->addChild(sprite);
        }
    }

    playing = true;
}
