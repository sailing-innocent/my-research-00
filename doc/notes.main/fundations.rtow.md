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

## 7. Antialiasing

We abstract camera class a bit so we can make a cooler camera later

### Some Ramdom Number Utilities

`<cstdlib> rand()`

### Generating Pixels with Multiple Samples

## 8. Diffuse Materials

Now that we have objects and multiple rays per pixel, we can make some realisitic looking materials.

define the max depth and diffuse through it.

At this step, the CPU is not that capable for rendering. We might consider some GPU acceleration tools.

```cpp
if (world.hit(r, 0, infinity, rec)) {
        point3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth-1);
    }
```

Now our sphere only absorb half of energy on each bounce

gamma corrected, meaning the 0 to 1 values have some transform before being stored to byte.

### Fixing Shadow Acne

Some of the reflected rays hit the object they are reflecting off of notn at exactly t = 0, but this might give t = -0.000001 or something.

so we can ignore values that are very near to 0

### True Lambertian Reflection

later we produces random points in the unit ball offset along the surface normal. But in reality, the distribution is not smooth.

very high in normal but low in gaze.

This distribution scales by $cos^3(\phi)$ where angle from the normal.

Lambertian distribution, which has a distribution of $\cos{\phi}$  True Lambertian has the probability higher for ray scattering close to normal. but the distribution is more uniform.

### An Alternative Diffuse Formulation

proven to be an incorrect approximation of ideal Lambertian diffuse.

A more intuitive approach is to have a uniform scatter direction for all angles away from the hit point.

without normal

You are encouraged to switch between the different diffuse renderers presented here.

## Metal

If we want different objects to have different materials, we have a design decision.

### Modeling Light Scatter and Reflectance

### Fuzzy reflection

we can also randomize the reflected direction by using a small sphere and choosing a new endpoint for the ray

## 10 Dieletrics

Clear Materials such as water, and diamonds are dielectrics. When a light ray hits them, it splits into a reflected ray and refracted ray.

### Snell's Law

The refraction is described as Snell's law

$$
\eta \sin{\theta} = \eta'\sin{\theta'}
$$

refractive indices, air = 1.0 and glass=1.3-1.7

构建左方向单位向量

$$
\frac{\mathbf{R}+\cos{\theta}\mathbf{n}}{\sin{\theta}}
$$

然后就很容易推导了

### Total Internal Reflection

That difinitely doesn't look right.

### Schlick Approximation

Real glass has reflectivity that varies with angles, but almost everybody uses an cheap and surprisingly accurate polynomial approximation

## 11 Positionable Camera

Cameras, like dielectrics, are a pain to debug.

### Camera Viewing Geometry

keep the rays comming from the origin and heading to the z = -1 plane}

### Positioning and Orienting the Camera

To get an arbitrary viewpoint.

- lookfrom
- lookat
- viewup: vup, v, w

## Defocus Blur

FINAL FEATURE!

all the photographers will call it "depth of field" (景深？)

- focal length: distance between the projection point and the image plane
- focus distance: the outsider distance where can get best focus

In a physical camera, the focus distance is controlled by the distance between the lens and film.

### A Thin Lens Approximation

A real camera has a complicated compound lens.

For our code we cound simulate the orderL sensor, then len, then aperture.

### Generating Sample Rays

遇到了一个奇怪的bug，看了半天原来是自己手贱把类中的u, v, w写了个auto，也就是根本就是零向量带入运算的，难怪出来的结果一点blur都没
