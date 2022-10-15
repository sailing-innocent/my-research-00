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
#include <ratio>
#include <chrono>

SAIL_NAMESPACE_BEGIN

/**
 * @class: Timer
 * @imple: sail/core/timer.cc
*/
class Timer {
public:
    Timer();
    long long TotalTime() const;
    long long DeltaTime() const;
    
    void Reset();
    void Start();
    void Stop();
    void Tick();
private:
    long long mDeltaTime;
    long long mBaseTime;
    long long mPausedTime;
    long long mStopTime;
    long long mPrevTime;
    long long mCurrTime;

    bool mStopped;
};

SAIL_NAMESPACE_END

#endif // SAIL_CORE_TIMER_H_
