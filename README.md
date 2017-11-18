## Summary

At university in 2015, I was tasked with creating a Java Swing GUI that rendered a Mandelbrot fractal, along with some other extensions like being able to zoom in or undo a zoom. This project is an attempt of recreating that using C++ and OpenGL.

## Dependencies

This project requires [cmake](https://cmake.org) for the build process and a c/c++ compiler for compiling the source code.

Internally this project uses [GLFW](https://github.com/glfw/glfw) for its window creation API and [glad](https://github.com/Dav1dde/glad) for its OpenGL loading library.

## Installation

* Clone the repository with the --recursive flag to grab all submodule dependencies.

```bash
# Clone the repository
git clone --recursive https://github.com/jordanlwest/Barebones-OpenGL-Project.git
```

* Make a build directory and run cmake in it for your particular build method.

```bash
cd Barebones-OpenGL-Project
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
