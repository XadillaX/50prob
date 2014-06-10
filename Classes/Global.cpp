#include "Global.h"
using namespace cocos2d;

const Size gameScreenSize = Size(480, 640);
CocosDenshion::SimpleAudioEngine* audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

long getMillionSeconds()
{
    timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}
