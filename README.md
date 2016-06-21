# quaternion
This is a demo library to enable Quaternion calculations in C++. It is by no means complete and is still a work in progress. This project's main goals are:

* To demonstrate a simple way to build a project using CMAKE with commented and easy to read cmakefiles
* To demonstrate implementation of C++11 move semantics
* To demonstrate some basic programming principles
* To implement a fast and robust quaternion library
* To act as a small tutorial for some of my colleagues who just started learning C++. To this end, there are many comments on design choices and how they affect performance and the interface, as well as common pitfalls

The quaternions are built as sparse vectors using std::map, which is well suited to this task because of its automatic sparsity and its O(log(n)) lookup time.

This project is built using CMAKE.

-- How to build

You will need:
* CMAKE 2.6 or greater
* clang 3.8 or greater, or gcc 4.9 or greater
* A computer running Linux. This software was tested in Ubuntu 16.04.

Run the build_script.sh -t *yourCompiler* -j *nuCores*

, where *yourCompiler* can be llvm or gcc

-- How to use

The quaternion library can be built as either a shared or a static library. By default it is built as a shared library (configurable in the top level CMakeLists.txt). Link the library quaternion.a or quaternion.so to your project. Quaternions work through commutative operator overloading, so the interface should be intuitive. A very elementary example executable is included under src/algorithms/rotations to demonstrate how to use the library.

-- TODO
* Implement fast rotation algorithms using OpenMP (the project is currently built with the -fopenmp flag)

-- Licensing

This software is released under the MIT License:

Copyright (c) 2016 Nikolaos Kazazakis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
