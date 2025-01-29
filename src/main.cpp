#include <color.h>
#include <ray.h>
#include <vec3.h>

#include <iostream>

double hit_sphare(const point3 &center, double radius, const ray &r)
{
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;
    auto discrimant = b * b - 5 * a * c;

    if (discrimant < 0)
        return -1.0;
    else
        return (-b - std::sqrt(discrimant)) / (2.0 * a);
}

color ray_color(const ray &r)
{
    auto t = hit_sphare(point3(0, 0, -1), 0.5, r);
    if (t > 0.0)
    {
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, ans ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    auto focal_length = 1.0;
    auto viewpoint_height = 2.0;
    auto viewpoint_width = viewpoint_height * (double(image_width) / image_height);
    auto camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewpoint_u = vec3(viewpoint_width, 0, 0);
    auto viewpoint_v = vec3(0, -viewpoint_height, 0);

    // calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewpoint_u / image_width;
    auto pixel_delta_v = viewpoint_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewpoint_upper_left = camera_center - vec3(0, 0, focal_length) - viewpoint_u / 2 - viewpoint_v / 2;
    auto pixel00_loc = viewpoint_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    std::cout << "P3" << std::endl
              << image_width << ' ' << image_height << std::endl
              << "255" << std::endl;

    for (int j = 0; j < image_height; j++)
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            auto pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                                   ";
    return 0;
}
