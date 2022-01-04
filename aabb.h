#ifndef AABB_H
#define AABB_H

#include "rtweekend.h"

class aabb {
    //! Axis-aligned bounding box
public:
    aabb() {}
    aabb(const point3 &a, const point3 &b) : minimum(a), maximum(b) {}
    // aabb could be defined by two points

    point3 min() const { return minimum; }
    point3 max() const { return maximum; }

    inline bool hit(const ray &r, double t_min, double t_max) const;

public:
    point3 minimum;
    point3 maximum;
};

inline bool aabb::hit(const ray &r, double t_min, double t_max) const {
    for (int axis = 0; axis < 3; axis++) {
        auto invD = 1.0 / r.direction()[axis];
        auto t0 = (min()[axis] - r.origin()[axis]) * invD;
        auto t1 = (max()[axis] - r.origin()[axis]) * invD;
        if (invD < 0)
            std::swap(t0, t1);
        t_min = t0 > t_min ? t0 : t_min; // find the biggese in the smallests
        t_max = t1 < t_max ? t1 : t_max; // find the smallest in the biggests

        if (t_max <= t_min)
            return false;
    }
    return true;
}

aabb surrounding_box(aabb box0, aabb box1) {
    point3 small(fmin(box0.min().x(), box1.min().x()),
                 fmin(box0.min().y(), box1.min().y()),
                 fmin(box0.min().z(), box1.min().z()));
    point3 big(fmax(box0.max().x(), box1.max().x()),
               fmax(box0.max().y(), box1.max().y()),
               fmax(box0.max().z(), box1.max().z()));

    return aabb(small, big);
}

#endif // implement BVH