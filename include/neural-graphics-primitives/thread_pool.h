/**
 * @file thread_pool.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include <neural-graphics-primitives/common.h>

#include <atomic>
#include <deque>
#include <functional>
#include <future>
#include <thread>
#include <vector>

NGP_NAMESPACE_BEGIN

template <typename T>
void waitAll(T&& futures) {
    for (auto& f: futures) {
        f.get();
    }
}

class ThreadPool {
public:
    ThreadPool();
    ThreadPool(size_t maxNumThreads, bool force = false);
    virtual ~ThreadPool();

    template <class F>
    auto enqueueTask(F&& f, bool highPriority = false) -> std::future<std::result_of_t <F()>> {
        using return_type = std::result_of_t<F()>;
        ++mNumTasksInSystem;

        auto task = std::make_shared<std::packaged_task<return_type()>>(std::forward<F>(f));

        auto res = task->get_future();

        {
            std::lock_guard<std::mutex> lock{mTaskQueueMutex};

            if (highPriority) {
                mTaskQueue.emplace_front([task]() {(*task)();});
            } else {
                mTaskQueue.emplace_back([task]() { (*task)();});
            }
        }
        
        mWorkerCondition.notify_one();
        return res;
    }

    void startThreads(size_t num);
    void shutdownThreads(size_t num);
    
    size_t numTasksInSystem() const {
        return mNumTasksInSystem;
    }

    void waitUntilFinished();
    void waitUntilFinishedFor(const std::chrono::microseconds Duration);
    void flushQueue();

    template <typename Int, typename F>
    void parallelForAsync(Int start, Int end, F body, std::vector<std::future<void>>& futures) {
        Int localNumThreads = (Int)mNumThreads;

        Int range = end - start;
        Int chunk = (range/localNumThreads) + 1;

        for (Int i = 0; i < localNumThreads; ++i) {
            futures.emplace_back(enqueueTask([i, chunkm start, end, body] {
                Int innerStart = start + i * chunk;
                Int innerEnd = std::min(end, start + (i + 1) * chunk);
                for (Int j = innerStart; j < innerEnd; ++j) {
                    body(j);
                }
            }));
        }
    }

    template <typename Int, typename F>
    std::vector<std::futre<void>> parallelForAsync(Int start, Int end, F body) {
        std::vector<std::future<void>> futures;
        parallelForAsync(start, end, body, futures);
        return futures;
    }

    template <typename Int, typename F>
    void parallelFor(Int start, Int end, F body) {
        waitAll(parallelForAsync(start, end, body));
    }
private:
    size_t nNumThreads = 0;
    std::vector<std::thread> mThreads;
    
    std::deque<std::function<void()>> mTaskQueue;
    std::mutex mTaskQueueMutex;
    std::condition_variable mWorkerCondition;

    std::atomic<size_t> mNumTasksInSystem;
    std::mutex mSystemBusyMutex;
    std::condition_variable mSystemBusyCondition;
}

NGP_NAMESPACE_END