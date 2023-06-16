#include <iostream>

#include "colour.h"
#include "hittable_list.h"
#include "rtweekend.h"
#include "sphere.h"
colour ray_colour(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + colour(1, 1, 1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * colour(1.0, 1.0, 1.0) + t * colour(0.5, 0.7, 1.0);
}

int main() {
    // image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 640;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // world
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    std::cerr << "horizontal: " << horizontal << "\n";
    std::cerr << "vertical: " << vertical << "\n";
    std::cerr << "origin: " << origin << "\n";

    auto lower_left_corner = origin - (horizontal / 2) - (vertical / 2) - vec3(0, 0, focal_length);
    std::cerr << "corner: " << lower_left_corner << "\n";
    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            // generating ray for each pixel in viewport
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            colour pixel_colour = ray_colour(r, world);
            write_colour(std::cout, pixel_colour);
        }
    }

    std::cerr << "\nDone\n";
}