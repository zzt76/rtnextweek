#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H

#include "rtweekend.h"

#include "aabb.h"
#include "hittable.h"

class moving_sphere : public hittable {
public:
    point3 center0, center1;
    double radius;
    shared_ptr<material> mat_ptr;
    double time0, time1;

public:
    moving_sphere() {}
    moving_sphere(point3 cen0, point3 cen1, double _time0,
                  double _time1, double r, shared_ptr<material> m)
        : center0(cen0), center1(cen1), time0(_time0),
          time1(_time1), radius(r), mat_ptr(m) {}

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
    point3 center(double time) const;
    virtual bool bounding_box(double _time0, double _time1, aabb &output_box) const override;
};

point3 moving_sphere::center(double time) const {
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool moving_sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    vec3 oc = r.origin() - center(r.time());
    vec3 dir = r.direction();
    double a = dir.length_squared();
    double half_b = dot(oc, dir);
    double c = oc.length_squared() - radius * radius;

    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return false;
    double sqrtd = sqrt(discriminant);

    // find the nearest hit point
    double root = (-half_b - sqrtd) / a;
    if (root < t_min || root > t_max) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || root > t_max)
            return false;
    }

    rec.t = root;
    rec.p = r.at(root);
    vec3 outward_normal = (rec.p - center(r.time())) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

bool moving_sphere::bounding_box(double _time0, double _time1, aabb &output_box) const {
    aabb box1 = aabb(center(_time0) - vec3(radius, radius, radius),
                     center(_time0) + vec3(radius, radius, radius));
    aabb box2 = aabb(center(_time1) - vec3(radius, radius, radius),
                     center(_time1) + vec3(radius, radius, radius));
    output_box = surrounding_box(box1, box2);
    return true;
}

#endif //define sphere class