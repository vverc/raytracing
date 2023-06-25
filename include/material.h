#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"

struct hit_record;

class material {
   public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation,
                         ray& scattered) const = 0;
};

class lambertian : public material {
   public:
    colour albedo;

    lambertian(const colour& a) : albedo(a) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation,
                         ray& scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();

        // catch bad scatter direction
        if (scatter_direction.near_zero()) {
            scatter_direction = rec.normal;
        }
        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;

        return true;
    }
};

class metal : public material {
   public:
    colour albedo;
    double fuzz;

    metal(const colour& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation,
                         ray& scattered) const override {
        auto reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;

        return (dot(scattered.direction(), rec.normal) > 0);
    }
};

#endif