#include "CItemLayer.h"
#include "Global.h"
using namespace cocos2d;

CItemLayer::CItemLayer() :
    dropping(false),
    playing(false),
    droppingTimer(0.0f),
    playTime(0.0f),
    isCalculatingTime(false)
{
}

CItemLayer::~CItemLayer()
{
    winLabel->release();
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

    // Time Label...
    timeLabel = LabelTTF::create("0.00 s", "Arial", 12);
    timeLabel->setAnchorPoint(Vec2(1, 0));
    this->addChild(timeLabel);
    timeLabel->setPosition(gameScreenSize.width - 10, 10);
    timeLabel->setColor(Color3B(0, 0, 0));

    // Smile and cry...
    smileAndCry = LabelTTF::create(":)    0\n:(    0", "Arial", 12);
    smileAndCry->setAnchorPoint(Vec2(0, 1));
    this->addChild(smileAndCry);
    smileAndCry->setHorizontalAlignment(TextHAlignment::LEFT);
    smileAndCry->setPosition(10, gameScreenSize.height - 10);
    smileAndCry->setColor(Color3B(0, 0, 0));

    // Win label
    winLabel = LabelTTF::create("", "Arial", 12);
    winLabel->retain();
    winLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    winLabel->setHorizontalAlignment(TextHAlignment::CENTER);
    winLabel->setPosition(gameScreenSize.width / 2.0f, gameScreenSize.height / 2.0f);
    winLabel->setColor(Color3B(0, 0, 0));

    // best score
    ValueMap vm = FileUtils::getInstance()->getValueMapFromFile("fastest");
    bestTime = vm["!"].asFloat();
    if(0.0 == bestTime)
    {
        bestTime = 999999;
    }
    char best[128];
    sprintf(best, "Best time to all right: %.2f s", bestTime);
    bestTimeLabel = LabelTTF::create(best, "Arial", 12);
    bestTimeLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    bestTimeLabel->setPosition(10, 10);
    bestTimeLabel->setColor(Color3B(0, 0, 0));
    this->addChild(bestTimeLabel);

    // 初始化...
    startNewGame();
}

void CItemLayer::onEnter()
{
    Layer::onEnter();

    // 手势侦听
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(CItemLayer::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(CItemLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    // 键盘侦听
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(CItemLayer::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // hint...
    auto hint = Sprite::create("hint.png");
    this->addChild(hint);
    hint->setPosition(gameScreenSize.width / 2, 307.0f);
    hint->setZOrder(-100);
    auto fadeOut = FadeOut::create(2.0f);
    auto delay = DelayTime::create(3.0f);
    hint->runAction(Sequence::create(delay, fadeOut, NULL));
}

void CItemLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if(!playing) return;

    if(keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        actions.push_back(TOA_LEFT);
    }
    else
    if(keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
    {
        actions.push_back(TOA_DOWN);
    }
    else
    if(keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        actions.push_back(TOA_RIGHT);
    }
}

bool CItemLayer::onTouchBegan(Touch* touch, Event* event)
{
    if(!playing) return true;

    startTouchPos = touch->getLocation();
    return true;
}

void CItemLayer::onTouchEnded(Touch* touch, Event* event)
{
    //Layer::onTouchEnded(touch, event);

    if(!playing)
    {
        startNewGame();
        return;
    }

    endTouchPos = touch->getLocation();

    // 判断方向
    auto delta = endTouchPos - startTouchPos;
    if(delta.length() < 20) return;

    // 横向
    if(fabs(delta.x) > fabs(delta.y))
    {
        if(fabs(delta.y) / fabs(delta.x) > 1.0f) return;

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
        if(fabs(delta.x) / fabs(delta.y) > 4.0f / 5.0f) return;

        if(delta.y < 0)
        {
            // 加入下边
            actions.push_back(TOA_DOWN);
        }
    }
}

void CItemLayer::updateSmileAndCry()
{
    static char count[25];
    sprintf(count, ":)    %d\n:(    %d", perCount[0], perCount[1]);
    smileAndCry->setString(count);
}

void CItemLayer::update(float delta)
{
    Layer::update(delta);

    static char timeStr[20];

    if(isCalculatingTime)
    {
        playTime += delta;

        sprintf(timeStr, "%.2f s", playTime);
        timeLabel->setString(timeStr);
    }

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

            if(!sprites.empty())
            {
                int j = 0;
                for(std::list<CItemSprite*>::iterator it = sprites.begin(); j < 6 && it != sprites.end(); it++, j++)
                {
                    CItemSprite* sprite = *it;
                    sprite->setCurrentPosition(5 - j);
                    sprite->setNextPosition(5 - j + 1);
                }
            }
            else
            {
                endGame();
                return;
            }

            dropping = false;
        }
    }
    else
    if(playing && !actions.empty())
    {
        if(!isCalculatingTime)
        {
            isCalculatingTime = true;
            playTime += delta;

            sprintf(timeStr, "%.2f s", playTime);
            timeLabel->setString(timeStr);
        }

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

        CItemSprite* first = sprites.front();
        if(actions.front() != first->rightAction())
        {
            // 错误
            first->setColor(Color3B(255, 0, 0));
            audioEngine->playEffect("SE.wav", false, 20.0f);
            perCount[1]++;
        }
        else
        {
            // 正确
            audioEngine->playEffect("SE.wav", false);
            perCount[0]++;
        }

        updateSmileAndCry();
        actions.pop_front();

        dropping = true;
    }
}

void CItemLayer::endGame()
{
    playing = false;
    dropping = false;
    isCalculatingTime = false;

    // 透明度
    smileAndCry->setOpacity(0);
    timeLabel->setOpacity(0);

    char str[128];
    sprintf(str, "Time: %.2f s\n:)    %d\n:(    %d\nTap to restart", playTime, perCount[0], perCount[1]);
    winLabel->setString(str);

    this->addChild(winLabel);

    // 如果全对而且最好
    if(perCount[0] == 50 && playTime < bestTime)
    {
        bestTime = playTime;
        char best[128];
        sprintf(best, "Best time to all right: %.2f s", bestTime);
        bestTimeLabel->setString(best);

        ValueMap vm;
        vm["!"] = bestTime;
        FileUtils::getInstance()->writeToFile(vm, "fastest");

        winLabel->setColor(Color3B(255, 0, 0));
    }
    else
    {
        winLabel->setColor(Color3B(0, 0, 0));
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

    playTime = 0.0f;
    isCalculatingTime = false;
    playing = true;
    perCount[0] = perCount[1] = 0;

    smileAndCry->setOpacity(255);
    timeLabel->setOpacity(255);
    timeLabel->setString("0.00 s");

    if(winLabel) this->removeChild(winLabel);

    updateSmileAndCry();
}
