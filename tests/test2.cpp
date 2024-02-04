#include "helpers/utils.hpp"

using namespace qua;


int main() {

    Time time_start = to_time("2017-01-03T01:10:00");

    Measurements unsampled = {
            m("2017-01-03T01:00:00", 35.79, measurement_type::temp),
            m("2017-01-03T01:10:00", 98.78, measurement_type::heart_rate),
            m("2017-01-03T01:50:00", 98.78, measurement_type::heart_rate),

    };

    print_measurements(unsampled);

    MeasurementsMap sampled = qua::sample(time_start, unsampled, interval::min * 5);

    print_measurements_map(sampled);

    MeasurementsMap expected = MeasurementsMap{
            {qua::measurement_type::heart_rate, Measurements{
                    m("2017-01-03T01:15:00", 98.78, measurement_type::heart_rate)
            }},
    };

    assert(sampled, expected);

    return 0;
}