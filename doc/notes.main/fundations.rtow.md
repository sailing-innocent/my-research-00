# Fundations.Ray-Tracing-One-Weekend

I strongly suggest everyone get started by this tutorial. It help you start to create your own rastering tools as soon as possible. Your own rastering tool plays a critical role when learning Computer Graphics. It will make abstract techniques practical, and make complicated concepts illustrated.

## Progress

## Index

- Overview
- Output an Image
- vec3 class
- Rays, a Simple Camera, and Background
- Adding a sphere
- Surfaces Normals and Multiple Objects
- Antialiasing
- Difuse Material
- Metal
- Dielectrics
- Positionalble Camera
- Defocus Blur

## Overview

## Output an Image

遇到了一个windows上的编码问题，需要注意输出时候的编码，Krita需要ascii编码的PPM文件才是可以识别，而 Powershell 默认的 UTF16-LE则不行。

`$PSDefaultParameterValues['Out-File:Encoding']='ascii'`

`$PSDefaultParameterValues['*:Encoding'] = 'ascii'`

真是令人头秃

## 6. Surface Normals and Multiple Objects

Shading With surface Normals

```cpp
#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return ( -b - sqrt(discriminant)) / (2.0 * a); // return the left points (frontend)
    }
}

color ray_color(const ray& r) {
    auto t = hit_sphere(point3(0,0,-1), 0.5, r);
    if (t > 0.0) {
        // hit 
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1)); // hit point - origin
        return 0.5 * color(N.x()+1, N.y()+1, N.z()+1);
    }
    // not hit, show background
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    const double aspect_ratio = 16.0/9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width/aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0,0,0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);

    auto lower_left_corner = origin - 0.5 * horizontal - 0.5 * vertical - vec3(0,0,focal_length);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / image_width;
            auto v = double(j) / image_height;
            ray r(origin, lower_left_corner+u*horizontal+v*vertical-origin);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}
```

Simplifying the Ray-Sphere Intersection Code

by using half_b to replace b

### An Abstraction for Hittable Objects

create a abstract class "hittable"

and derived a sphere class from hittable 

### Front Faces Versus Back Faces

We need to choose one of the the posibilities (ray in or out the surface) because we will eventually want to determine which side of the surface that the ray is coming from.

### hittable list

combine a series of hittable object into a big hittable

### Some New C++ Features

vector and shared_ptr

shared_ptr is a pointer to some allocated type, with reference-counting semantics. Every time you assign its value to another shared pointer, the reference count is incremented.

Once the count goes to zero, the object is deleted.

included with `<memory> header`
