#pragma once

#include <Eigen/Core>
namespace eg = Eigen;
class SecondOderModule
{
public:
    double in;
    double out;
    double Ts;
    SecondOderModule();
    void Step();

private:
    eg::Vector2d x;
    eg::Matrix2d A;
    eg::Vector2d B;
    eg::RowVector2d C;
    double D;
};