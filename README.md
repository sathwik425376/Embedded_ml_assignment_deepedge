# Embedded ML Assignment – Image Resizing with OpenCV and Custom Implementation

This project is a part of the Embedded Machine Learning course. It explores image resizing using OpenCV and custom C++ implementations to compare speed and accuracy of different interpolation methods.

---

## 📚 Steps Covered

### ✅ Step 1: Image Read, Display, and Resize using OpenCV (Python)

- Load a `.bmp` image
- Display the original image
- Resize the image to half its original size using OpenCV’s `cv2.resize()` with three methods:
  - `INTER_NEAREST`
  - `INTER_LINEAR`
  - `INTER_CUBIC`
- Save the resized images

#### 🔧 File:
- `resize_opencv.py`

#### 🏁 Output:
- `resize_nearest.bmp`
- `resize_linear.bmp`
- `resize_cubic.bmp`

---

### ✅ Step 2: Resize Benchmark using OpenCV (C++)

- Load an image using OpenCV (`imread`)
- Resize it to half size using `cv::resize()`
- Measure time for each interpolation method over **1000 iterations**
- Save and display resized images

#### 🔧 File:
- `resize_benchmark.cpp`

#### 🛠 Compile:

```bash
g++ resize_benchmark.cpp -o resize_benchmark.exe -I C:/msys64/ucrt64/include/opencv4 -L C:/msys64/ucrt64/lib -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
