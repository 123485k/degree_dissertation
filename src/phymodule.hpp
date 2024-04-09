#pragma once

#include <cstdint>

class Module {
public:
  double env_temp;
  double temp;
  uint32_t Ts;
  Module(double init_temp, double env_temp);
  void Step();
};