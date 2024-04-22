
#include <unistd.h>

#include <condition_variable>
#include <iostream>
#include <thread>

#include "modbus-server.hpp"
#include "phymodule.hpp"

using std::atomic;
using std::condition_variable;
using std::mutex;
using std::unique_lock;

int main(int argc, char **argv) {
  std::cout << "starting server\n";
  std::string portstr = "1502"; //
  std::cout << "listen on " << portstr << "\n"; 
  ModbusSlave Server("0.0.0.0", portstr); // init server
  Server.run(); // start server
  SecondOderModule M;

  atomic<bool> running{true};
  mutex mtx;
  condition_variable cv;
  auto next_execution_time =
      std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(5);
  std::thread loop([&]() {
    while (running) {
      unique_lock<mutex> lck(mtx);
      cv.wait_until(lck, next_execution_time, [&]() { return running.load(); });
      if (!running.load()) break;

      M.in = Server.getRegFloat_cdab(73);
      M.Step();
      Server.setInputRegFloat_dcba(73, M.out);
      next_execution_time += std::chrono::milliseconds(5);
    }
  });
  cv.notify_all();
  loop.detach();

  while (1) {
  }
  return 0;
}