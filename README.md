## Summary

For one of my projects at university, I was tasked with creating a Java Swing GUI that rendered a Mandelbrot fractal, along with some other extensions like being able to zoom in or undo a zoom. This project is an attempt of recreating that using C++ and OpenGL.

## Dependencies

This project requires [cmake](https://cmake.org) for the build process and a c/c++ compiler for compiling the source code.

Internally this project uses [GLFW](https://github.com/glfw/glfw) for its window creation API and [glad](https://github.com/Dav1dde/glad) for its OpenGL loading library.

## Installation

* Clone the repository with the --recursive flag to grab all submodule dependencies.

```bash
# Clone the repository
git clone --recursive https://github.com/jordanlwest/FractalExplorer.git
```

* Make a build directory and run cmake in it for your particular build method.

```bash
cd FractalExplorer 
mkdir build
cd build/

# For Makefiles
cmake ../

# For Visual Studio Solution
cmake -G "Visual Studio 15 2017" ../
```

* Compile and build the project using your build method. 

```
make
```

## Keybindings

* Left click an area to zoom in.
* Right click to undo a previous zoom.
* Up and down arrow keys to raise or lower the maximum number of iterations for Mandelbrot generation.
* R to reset to the initial configuration.

## TODO

* URGENT - shaders rely on relative path from build folder, copy them during compilation process to build folder instead?
* Implement additional fractals (e.g. Burning Ship, Julia Set, Sierpinski Carpet/Triangle)
* Implement a graphical user interface to provide controls and information relating to the current fractal.
* Work on numerical precision to allow for further zooming.
