#include "phymodule.hpp"

SecondOderModule::SecondOderModule()
    : in(0),
      out(0),
      Ts(10e-3),
      x{0, 0},
      A{{-0.0400, -0.0400}, {1.0000, 0}},
      B({1, 0}),
      C{0, 4.0000},
      D(0) {}
void SecondOderModule::Step() {
  x += Ts * (A * x + B * in);
  out = (C * x)(0, 0) + D * in;
}