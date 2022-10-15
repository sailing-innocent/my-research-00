/**
 * FILE: sail/core/timer.cc
 * AUTHOR: sailing-innocent
 * CREATE: 2022-10-15
 * DESP: mainly the encrypt for std::chronno library
 * DONE: //TODO
*/
#include <sail/core/timer.hpp>


SAIL_NAMESPACE_BEGIN

using std::chrono::system_clock;

long long NowInLongLong() {
    return (long long)std::chrono::duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch()).count();
}

Timer::Timer():
    mDeltaTime(-1),
    mBaseTime(0),
    mPausedTime(0),
    mPrevTime(0),
    mStopTime(0),
    mCurrTime(0),
    mStopped(false)
{}

long long Timer::TotalTime() const 
{
    if (mStopped)
    {
        return  (long long)((mStopTime - mPausedTime) - mBaseTime);
    }
    else
    {
        return (long long)((mCurrTime - mPausedTime) - mBaseTime);
    }
}

long long Timer::DeltaTime() const
{
    return (long long)mDeltaTime;
}

void Timer::Reset()
{
    long long currTime = NowInLongLong() ;
    mBaseTime = currTime;
    mPrevTime = currTime;
    mStopTime = 0;
    mStopped = false;
}

void Timer::Start() {
    long long startTime = NowInLongLong();
    if (mStopped)
    {
        mPausedTime += (startTime - mStopTime);

        mPrevTime = startTime;
        mStopTime = 0;
        mStopped = false;
    }
}

void Timer::Stop() {
    if (!mStopped) {
        long long currTime = NowInLongLong() ;

        mStopTime = currTime;
        mStopped = true;
    }
}

void Timer::Tick() {
    // record but not stop
    if (mStopped) {
        mDeltaTime = 0;
        return;
    }

    long long currTime = NowInLongLong();
    mCurrTime = currTime;
    mDeltaTime = mCurrTime - mPrevTime;
    mPrevTime = mCurrTime;

    if (mDeltaTime < 0)
    {
        mDeltaTime = 0;
    }
}

SAIL_NAMESPACE_END