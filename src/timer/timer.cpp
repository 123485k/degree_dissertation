#include "timer.hpp"

namespace mytimer {

void PeriodicTimer::start() {
  running_ = true;
  thread_ = std::thread{&PeriodicTimer::run, this};
}

void PeriodicTimer::stop() {
  running_ = false;
  if (thread_.joinable()) {
    thread_.join();
  }
}

void PeriodicTimer::run() {
  TimePoint next_execution_time = Clock::now();

  while (running_) {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait_until(lock, next_execution_time, [this] { return !running_; });

    if (!running_) {
      break;
    }

    // 执行任务
    task_();
    next_execution_time += interval_;
  }
}

}  // namespace mytimer