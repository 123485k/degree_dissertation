#include "phymodule.hpp"

Module::Module(double init_temp, double env_temp)
    : temp(init_temp), env_temp(env_temp),Ts(5) {
        
    }