#include "qua.hpp"

namespace qua {
    MeasurementsMap sample(Time time_start, Measurements unsampled, unsigned long interval_ns) {
        std::sort(unsampled.begin(), unsampled.end(), [](const Measurement &a, const Measurement &b) -> bool {
            return a.time < b.time;
        });

        MeasurementsMap output = {};
        std::unordered_map<std::string, std::tuple<Time, Measurement>> sample_boxes = {};

        for (const Measurement &sample: unsampled) {
            std::string key = sample.type;

            if (sample.time < time_start) {
                continue;
            }

            auto sample_box = sample_boxes.find(key);

            if (sample_box == nullptr) {
                sample_boxes.insert_or_assign(key, std::make_tuple(time_start, sample));
                continue;
            }

            auto [previous_interval_end, current_sample] = sample_box->second;
            Time current_interval_end = previous_interval_end + std::chrono::nanoseconds(interval_ns);
            Time next_interval_end = previous_interval_end + std::chrono::nanoseconds(2 * interval_ns);

            if (sample.time <= current_interval_end) {
                sample_boxes.insert_or_assign(key, std::make_tuple(previous_interval_end, sample));
                continue;
            }

            if (sample.time > current_interval_end && sample.time <= next_interval_end) {
                Measurements *vec = &output[sample.type];
                vec->emplace_back(current_interval_end, current_sample.value, current_sample.type);
                sample_boxes.insert_or_assign(key, std::make_tuple(current_interval_end, sample));
                continue;
            }

        }

        for (auto index: sample_boxes) {
            const auto [key, value] = index;
            auto [current, sampled] = value;
            Measurements *vec = &output[sampled.type];
            vec->emplace_back(current + std::chrono::nanoseconds(interval_ns), sampled.value, sampled.type);
        }

        return output;
    }

    bool operator==(const Measurement &first, const Measurement &second) {
        return first.time == second.time && first.type == second.type && first.value == second.value;
    }
}