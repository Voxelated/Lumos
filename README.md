# Lumos

Lumos is Voxel's window management and rendering library. It attempts to use
Vulkan for rendering when possible (any platform other than iOS/OSX), and
reverts to using OpenGL when Vulkan is not supported by the platform.

# Compiler Support

Lumos is developed using the following compilers and versions:

------------------------------------
| Platform | Compiler    | Version |
|:--------:|:-----------:|:--------|
| OSX			 | Apple Clang | 9.0.0 	 |
------------------------------------

# Window System

The window system interfaces with the following APIs depending on the platform
on which Lumos is running:

--------------------------
| Platform | Window API  |
|:--------:|:-----------:|
| OSX			 | Apple Clang |
--------------------------

# Getting Started
