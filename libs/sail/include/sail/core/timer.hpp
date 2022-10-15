#pragma once

/**
 * FILE: include/sail/core/timer.hpp
 * AUTHOR: sailing-innocent
 * CREATE: 2022-10-15
 * DESP: The Sail Timer Class Definitions
*/

#ifndef SAIL_CORE_TIMER_H_
#define SAIL_CORE_TIMER_H_

#include <sail/core.h>

SAIL_NAMESPACE_BEGIN

/**
 * @class: Timer
 * @imple: sail/core/timer.cc
*/
class Timer {
public:
    Timer();
    float TotalTime() const;
    float DeltaTime() const;
    
    void Reset();
    void Start();
    void Stop();
    void Tick();
private:
    double mSecondsPerCount;
    double mDeltaTime;

    __int64 mBaseTime;
    __int64 mPausedTime;
    __int64 mStopTime;
    __int64 mPrevTime;
    __int64 mCurrTime;

    bool mStopped;
};

SAIL_NAMESPACE_END

#endif // SAIL_CORE_TIMER_H_
