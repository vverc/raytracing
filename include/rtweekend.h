#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// usings
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// utility functions
inline double degrees_to_radians(double degrees) { return degrees * pi / 180.0; }

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// random
inline double random_double() {
    // returns a random real is [0,1)
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // returns a random real in [min, max)
    return min + (max - min) * random_double();
}

// common headers
#include "ray.h"
#include "vec3.h"

#endif
