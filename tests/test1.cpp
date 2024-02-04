#include "helpers/utils.hpp"

using namespace qua;

int main() {
    Time time_start = to_time("2017-01-03T10:00:00");

    Measurements unsampled = {
            m("2017-01-03T10:04:45", 35.79, measurement_type::temp),
            m("2017-01-03T10:01:18", 98.78, measurement_type::spo2),
            m("2017-01-03T10:09:07", 35.01, measurement_type::temp),
            m("2017-01-03T10:03:34", 96.49, measurement_type::spo2),
            m("2017-01-03T10:02:01", 35.82, measurement_type::temp),
            m("2017-01-03T10:05:00", 97.17, measurement_type::spo2),
            m("2017-01-03T10:05:01", 95.08, measurement_type::spo2),
    };


    print_measurements(unsampled);
    MeasurementsMap sampled = sample(time_start, unsampled, interval::min * 5);

    print_measurements_map(sampled);

    MeasurementsMap expected = MeasurementsMap{
            {qua::measurement_type::temp, Measurements{
                    m("2017-01-03T10:05:00", 35.79, measurement_type::temp),
                    m("2017-01-03T10:10:00", 35.01, measurement_type::temp)
            }},
            {qua::measurement_type::spo2, Measurements{
                    m("2017-01-03T10:05:00", 97.17, measurement_type::spo2),
                    m("2017-01-03T10:10:00", 95.08, measurement_type::spo2)
            }}
    };


    assert(sampled, expected);

    return 0;
}