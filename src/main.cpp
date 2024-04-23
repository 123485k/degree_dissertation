#include <iostream>
#include <string>

#include "CLI/CLI.hpp"
#include "modbus-server.hpp"
#include "phymodule.hpp"
#include "timer.hpp"
using namespace mytimer;

int main(int argc, char** argv) {
  CLI::App app{"Modbus Server"};

  std::string listen_address = "0.0.0.0";
  int port = 502;

  app.add_option("-l,--listen", listen_address, "Server listening address")
      ->capture_default_str();
  app.add_option("-p,--port", port, "Server listening port")
      ->capture_default_str();
  try {
    app.parse(argc, argv);
  } catch (const CLI::ParseError& e) {
    return app.exit(e);
  }

  std::cout << "Starting server\n";
  std::cout << "Listen on " << listen_address << ":" << port << "\n";

  ModbusSlave Server(listen_address, std::to_string(port));  // init server
  Server.run();                                              // start server

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