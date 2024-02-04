#include "helpers/utils.hpp"

using namespace qua;


int main() {

    Time time_start = to_time("2017-01-03T01:10:00");

    Measurements unsampled = {
            m("2017-01-03T01:10:00", 1.79, measurement_type::temp),
            m("2017-01-03T01:10:05", 2.79, measurement_type::temp),
            m("2017-01-03T01:10:06", 3.79, measurement_type::temp),
            m("2017-01-03T01:10:10", 4.79, measurement_type::temp),
            m("2017-01-03T01:10:05", 5.78, measurement_type::heart_rate),
            m("2017-01-03T01:10:05", 6.78, measurement_type::heart_rate),
            m("2017-01-03T01:10:10", 7.78, measurement_type::heart_rate),
    };

    print_measurements(unsampled);

    MeasurementsMap sampled = qua::sample(time_start, unsampled, interval::s * 5);

    print_measurements_map(sampled);

    MeasurementsMap expected = MeasurementsMap{
            {qua::measurement_type::temp,       Measurements{
                    m("2017-01-03T01:10:05", 2.79, measurement_type::temp),
                    m("2017-01-03T01:10:10", 4.79, measurement_type::temp),
            }},
            {qua::measurement_type::heart_rate, Measurements{
                    m("2017-01-03T01:10:05", 6.78, measurement_type::heart_rate),
                    m("2017-01-03T01:10:10", 7.78, measurement_type::heart_rate),
            }},
    };

    assert(sampled, expected);

    return 0;
}