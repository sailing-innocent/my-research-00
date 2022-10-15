/**
 * FILE: sail/core/timer.cc
 * AUTHOR: sailing-innocent
 * CREATE: 2022-10-15
 * DESP: mainly the encrypt for std::chronno library
*/
#include <sail/core/timer.hpp>

SAIL_NAMESPACE_BEGIN

Timer::Timer():
    mSecondsPerCount(0.0),
    mDeltaTime(-1.0),
    mBaseTime(0),
    mPausedTime(0),
    mCurrTime(0),
    mStopped(false)
{
    __int64 countsPerSec;

}

SAIL_NAMESPACE_END