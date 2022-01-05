#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>

// usings
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// utility functions
inline double degrees_to_radians(double degrees) {
    return degrees / 180.0 * pi;
}

inline double random_double() {
    // if use traditional not static rand() with multi-thread will yield incorrect results
    // more efficient and safe
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

// inline double random_double() {
//     return rand() / (RAND_MAX + 1.0);
// }

inline double random_double(int seed) {
    srand(seed);
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    return random_double() * (max - min) + min;
}

inline double random_int(int min, int max) {
    return static_cast<int>(random_double(min, max + 1));
}

inline double clamp(double x, double min, double max) {
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

// common headers

#include "ray.h"
#include "vec3.h"

#endif // include useful header files