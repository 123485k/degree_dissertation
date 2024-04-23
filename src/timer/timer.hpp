#pragma once

#include <chrono>
#include <condition_variable>
#include <functional>
#include <thread>

namespace mytimer
{

class PeriodicTimer
{
public:
    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;

    // 构造函数，接受带捕获列表的lambda表达式
    template <typename Lambda>
    PeriodicTimer(std::chrono::milliseconds interval, Lambda&& task)
        : interval_{interval}, task_{std::forward<Lambda>(task)}
    {
    }

    // 启动定时器
    void start();

    // 停止定时器
    void stop();

private:
    void run();

    bool running_ = false;
    std::thread thread_;
    std::function<void()> task_;
    std::chrono::milliseconds interval_;
    std::condition_variable cv_;
    std::mutex mutex_;
};

}  // namespace mytimer