#include "phymodule.hpp"


SecondOderModule::SecondOderModule()
    : in(0),
      out(0),
      Ts(5e-3),
      x{0, 0},
      A{{-7, -9}, {1, 0}},
      B({1, 0}),
      C{2, 1},
      D(0) {}
void SecondOderModule::Step() {
  x += Ts * (A * x + B * in);
  out = (C * x)(0, 0) + D * in;
}