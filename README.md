# Volumetric Cloud
## Introduction
A little coding challenge for myself. Attempting to recreate volumetric cloud in real-time from scratch, using GLSL and C++ based on [Fredrik Häggström's paper](http://www.diva-portal.org/smash/get/diva2:1223894/FULLTEXT01.pdf).

This repository consists of two programs, please view markdown file in each project folder for further information.
- [VolumetricCloud](VolumetricCloud/README.md)
- [MapGenerator](MapGenerator/README.md)

## Build
First make sure you have Visual Studio 2017 or above installed on your machine. This repository uses [premake5](https://github.com/premake/premake-core) to generate project files. Execute `setup_vs2017` or `setup_vs2019` to generate Visual Studio solution file.

## Dependencies
| Name  | Description |
| :---: | :---------- |
| [CLI11](https://github.com/CLIUtils/CLI11) | CLI11 is a command line parser for C++11 and beyond that provides a rich feature set with a simple and intuitive interface. |
| [glm](https://github.com/g-truc/glm) | OpenGL Mathematics (GLM) |
| [premake](https://github.com/premake/premake-core) | Powerfully simple build configuration. |
| [stb_image_write](https://github.com/nothings/stb/blob/master/stb_image_write.h) | stb single-file public domain libraries for C/C++ |