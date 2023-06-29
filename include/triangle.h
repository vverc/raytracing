#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"
#include "vec3.h"

class triangle : public hittable {
   public:
    point3 v0, v1, v2;
    shared_ptr<material> mat_ptr;

    triangle() {}
    triangle(point3 ver0, point3 ver1, point3 ver2, shared_ptr<material> m)
        : v0(ver0), v1(ver1), v2(ver2), mat_ptr(m){};

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};

bool triangle::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 n = cross(v1 - v0, v2 - v0);

    // get plane - ray intersection
    // check ray and plane aren't parallel
    if (dot(n, r.direction()) < 0) return false;

    // find root that gives plane intersection
    auto d = -dot(n, v0);
    auto root = -(dot(n, r.origin()) + d) / dot(n, r.direction());

    if (root < t_min || t_max < root) return false;

    point3 p = r.at(root);

    // check that p lies within the triangle
    vec3 c0, c1, c2;

    c0 = cross(v1 - v0, p - v0);
    c1 = cross(v2 - v1, p - v1);
    c2 = cross(v0 - v2, p - v2);

    if (dot(n, c0) < 0 || dot(n, c1) < 0 || dot(n, c2) < 0) return false;

    vec3 outward_normal = n;
    rec.p = p;
    rec.t = root;
    rec.set_face_normal(r, unit_vector(outward_normal));
    rec.mat_ptr = mat_ptr;

    return true;
}

#endif
