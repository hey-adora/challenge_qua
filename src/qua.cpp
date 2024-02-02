#include "qua.hpp"

namespace qua {
    MeasurementsMap sample(Time time_start, Measurements unsampled) {
        std::sort(unsampled.begin(), unsampled.end(), [](const Measurement &a, const Measurement &b) -> bool {
            return a.time < b.time;
        });

        MeasurementsMap output = {};
        std::unordered_map<std::string, std::tuple<Time, Measurement>> current_samples = {};

        for (const Measurement &sample: unsampled) {
            std::string key = sample.type;

            if (sample.time < time_start) {
                continue;
            }

            auto current_sample_pair = current_samples.find(key);

            if (current_sample_pair == nullptr) {
                current_samples.insert_or_assign(key, std::make_tuple(time_start, sample));
                continue;
            }

            auto [time_current, current_sample] = current_sample_pair->second;
            Time time_middle = time_current + std::chrono::minutes(5);
            Time time_max = time_current + std::chrono::minutes(10);

            if (sample.time <= time_middle && sample.time > time_start) {
                current_samples.insert_or_assign(key, std::make_tuple(time_current, sample));
                continue;
            }

            if (sample.time > time_middle && sample.time < time_max) {
                if (!output.contains(sample.type)) {
                    output[sample.type] = Measurements{};
                }
                Measurements *vec = &output[sample.type];

                vec->emplace_back(time_middle, current_sample.value, current_sample.type);
                current_samples.insert_or_assign(key, std::make_tuple(time_middle, sample));
                continue;
            }

        }

        for (auto index: current_samples) {
            const auto [key, value] = index;
            auto [current, sampled] = value;
            Measurements *vec = &output[sampled.type];
            vec->emplace_back(current + std::chrono::minutes(5), sampled.value, sampled.type);
        }

        return output;
    }

    bool operator==(const Measurement &first, const Measurement &second) {
        return first.time == second.time && first.type == second.type && first.value == second.value;
    }
}