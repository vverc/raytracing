# raytracing

red_circle.ppm
detecting a circle

sphere_with_surface_normals.ppm
detecting the sphere and also calculating the normals of the ray intersections.
x/y/z mapped to r/g/b

multiple_hittables.ppm
created hittable abstract class
created sphere class from hittable
store hit_detection within hittables class

diffuse_spheres
we calculate randomized reflection rays by taking a random point where x, y, z are within [-1.1)
reject rays that lie outside of our tangential sphere centered about the normal from the hit point

diffuse_sphere_depth_limit.ppm
sphere with matte material
diffuse objects modulate reflected light with thier own color
light reflected off a diffuse surface have random directions

diffuse_sphere_lambertian.ppm
previous sphere had rays concentrated about the normal, lambertian distribution is more uniform.

diffuse_sphere_hemispherical_scatter.ppm
reflected rays scatter in a hemisphere centered around hit point

metal_spheres.ppm
scene with 2 different materials, diffuse and metal.

metal_spheres_with_fuzz.ppm
metal materials with fuzzy reflections. fuzz implemented by randomly adjusting reflected rays within a sphere centered about the endpoint
