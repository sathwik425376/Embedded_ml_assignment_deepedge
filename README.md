# Embedded ML Assignment – Image Resizing with OpenCV and Custom Implementation

This project is a part of the Embedded Machine Learning course. It explores image resizing using OpenCV and custom C++ implementations to compare speed and accuracy of different interpolation methods.

---

## steps covered
STEPs 1&2
This extend illustrates how to **resize a BMP picture** to **half its unique measurements** utilizing **three distinctive insertion strategies** in OpenCV. It too benchmarks the execution by measuring the **execution time for 1000 cycles** of each strategy.
## FEATURES
Peruses an input BMP picture utilizing OpenCV.
- Resizes the picture utilizing three introduction methods:
- `INTER_NEAREST`
- `INTER_LINEAR`
- `INTER_CUBIC`
- Benchmarks the execution by rehashing each strategy 1000 times.
- Spares resized pictures to disk for comparison.
## FILE STUCTURE
── main.cpp # Main C++ program
├── input.bmp # Input image (provide your own)
├── resized_INTER_NEAREST.bmp # Output image - nearest interpolation
├── resized_INTER_LINEAR.bmp # Output image - linear interpolation
├── resized_INTER_CUBIC.bmp # Output image - cubic interpolation
└── README.md # Project documentation
## REQUIRMENTS
- OpenCV (version 3.x or 4.x)
- C++17 or later
- CMake (optional)
- A C++ compiler 
## How to Run
Replace the path of the image in main.cpp with the path of your .BMP image
## output
The console shows the time taken by each of the interpolation methods
the resized images are saved 
resized_INTER_NEAREST.bmp
resized_INTER_LINEAR.bmp
resized_INTER_CUBIC.bmp
## steps covered
step 3
## Building Your Own Image Resizer in C++ and Timing analysis
This project implements **custom image resizing algorithms** in C++ using OpenCV. It replicates the behavior of OpenCV’s built-in `cv::resize()` function using three interpolation techniques:
- Nearest Neighbor
- Bilinear Interpolation
- Bicubic Interpolation
Each method resizes an image to **half its original dimensions** and benchmarks the time taken for **1000 iterations** to provide a performance comparison.
## Need of the project
While OpenCV provides powerful built-in functions for image resizing, understanding how these methods work internally helps in:

- Deepening your knowledge of interpolation algorithms.
- Learning how to manipulate image matrices manually.
- Understanding computational trade-offs of each method.
## project stucture
_ main.cpp # Main C++ program with custom resizing functions
_input.bmp # Input image (you need to provide your own BMP image)
_custom_INTER_NEAREST.bmp # Output from custom nearest-neighbor interpolation
_custom_INTER_LINEAR.bmp # Output from custom bilinear interpolation
_custom_INTER_CUBIC.bmp # Output from custom bicubic interpolation
_README.md # This documentation
## requirments 
OpenCV (3.x or 4.x)
- C++17 or later
- g++, clang++, or MSVC compiler
- CMake
## How to run
Replace the hardcoded image path in main.cpp
Run the program
Outputs:
The program resizes the image using each interpolation method 1000 times.

Saves output images:custom_INTER_NEAREST.bmp

custom_INTER_LINEAR.bmp

custom_INTER_CUBIC.bmp
Prints timing results in the console

## THE END ##