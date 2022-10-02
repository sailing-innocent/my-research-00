/**
 * @file shared_queue.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <condition_variable>
#include <deque>
#include <mutex>

NGP_NAMESPACE_BEGIN

class ICallable {
public:
    virtual ~ICallable() {}
    virtual void operator()()=0;
};

template <typename T>
class Callable: public ICallable {

};

template <typename T>
std::unique_ptr<ICallable> callable(T&& callable) {
    return std::make_shared<Callable<T>>(std::forward<T>(callable));
}

class SharedQueueEmptyException {};

template <typename T>
class SharedQueue {
public:
    bool empty() const {
        std::lock_guard<std::mutex> lock{mMutex};
        return mRawQueue.empty();
    }
private:
    std::deque<T> mRawQueue;
    mutable std::mutex mMutex;
    std::condition_variable mDataCondition;
};

NGP_NAMESPACE_END
