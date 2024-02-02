#include "utils.hpp"

using namespace qua;

void print_measurements(const Measurements &samples) {
    std::cout << "----INPUT----\n";
    for (const Measurement &sample: samples) {
        std::cout << sample.type << ": "
                  << std::format("{:%Y-%m-%dT%H:%M:%OS}", std::chrono::zoned_time("Europe/Vilnius", sample.time))
                  << " " << sample.value
                  << std::endl;
    }
}

void print_measurements_map(const qua::MeasurementsMap &measurements_map) {
    std::cout << "----OUTPUT----\n";
    for (const std::pair<const std::string, Measurements> &sampled_measurements: measurements_map) {
        for (const Measurement &sample: sampled_measurements.second) {
            std::cout << sample.type << ": "
                      << std::format("{:%Y-%m-%dT%H:%M:%OS}", std::chrono::zoned_time("Europe/Vilnius", sample.time))
                      << " " << sample.value << std::endl;
        }

    }
}

Measurement m(const std::string &time, double value, const std::string &type) {
    return Measurement{to_time(time), value, type};
}


Time to_time(const std::string &str) {
    std::tm tm = {};
    std::istringstream ss(str);
    ss >> std::get_time<char>(&tm, "%Y-%m-%dT%H:%M:%OS");
    auto t = std::mktime(&tm);
    Time tp = std::chrono::system_clock::from_time_t(t);
    return tp;
}