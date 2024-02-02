#pragma once

#include <stdexcept>
#include "qua.hpp"

using namespace qua;

void print_measurements(const Measurements &samples);

void print_measurements_map(const qua::MeasurementsMap &measurements_map);

Time to_time(const std::string &str);

Measurement m(const std::string &time, double value, const std::string &type);

template<typename T>
void assert(T x, T y) {
    if (x != y) {
        throw std::runtime_error("Wrong result.");
    }
}
