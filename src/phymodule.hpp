#pragma once

#include <Eigen/Core>

class SecondOderModule {
 public:
  double in;
  double out;
  double Ts;
  SecondOderModule();
  void Step();

 private:
  Eigen::Vector2d x;
  Eigen::Matrix2d A;
  Eigen::Vector2d B;
  Eigen::RowVector2d C;
  double D;
};