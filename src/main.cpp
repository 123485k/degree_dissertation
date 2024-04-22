
#include <unistd.h>

#include <iostream>

#include "modbus-server.hpp"
#include "phymodule.hpp"
#include "timer.hpp"
using namespace mytimer;
int main(int argc, char **argv) {
  std::cout << "starting server\n";
  std::string portstr = "1502";  //
  std::cout << "listen on " << portstr << "\n";
  ModbusSlave Server("0.0.0.0", portstr);  // init server
  Server.run();                            // start server
  SecondOderModule M;
  PeriodicTimer timer(std::chrono::milliseconds{10}, [&]() {
    M.in = Server.getRegFloat_cdab(73);
    M.Step();
    Server.setInputRegFloat_dcba(73, M.out);
  });
  timer.start();
  while (1) {
  }
}