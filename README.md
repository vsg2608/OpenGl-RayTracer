# OpenGl-RayTracer

This program involves implementation of recursive ray tracing with the following features

A scene with objects of the type: polygon (plane), and sphere, quadric and a box. While specifying the object one needs to give the geometry and material properties.
Local illumination model (Phong) with diffuse, specular and ambient components.
Multiple light sources.
Global illumination with reflection, refraction and shadows.
Implement anti-aliasing using supersampling.
Input using a file (your own format or a general format e.g. povray compliant)
Specify eye/camera in viewing coordinate system (VCS) as done in the viewing pipe line.
Perform intersection computation in world coordinate system (WCS). This would require appropriate transformation from VCS to WCS and vice versa.
The final image can be rendered using OpenGL (3.0 or above) or any suitable image preview/display tool.
