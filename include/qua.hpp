#pragma once

#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <unordered_map>

namespace qua {
    typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<long, std::ratio<1, 1000000000>>> Time;
    typedef std::chrono::duration<long, std::ratio<1, 1000000000>> Duration;

    namespace measurement_type {
        static std::string temp = "temp";
        static std::string heart_rate = "heart_rate";
        static std::string spo2 = "spo2";
    }

    struct Measurement {
        Time time;
        double value{};
        std::string type;

        Measurement(Time time, double value, std::string type) : time(time), value(value), type(std::move(type)) {}
    };

    bool operator==(const Measurement &first, const Measurement &second);


    using MeasurementsMap = std::unordered_map<std::string, std::vector<Measurement>>;
    using Measurements = std::vector<Measurement>;

    MeasurementsMap sample(Time time_start, Measurements unsampled);
}