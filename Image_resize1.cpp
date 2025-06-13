#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

void resize_and_time(const Mat& input, int interpolation, const string& method_name) {
    Mat resized;
    int new_width = input.cols / 2;
    int new_height = input.rows / 2;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
        resize(input, resized, Size(new_width, new_height), 0, 0, interpolation);
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();

    cout << "Time taken for 1000 iterations using " << method_name << ": " << duration << " ms" << endl;

   
    imwrite("resized_" + method_name + ".bmp", resized);
}

int main() {
    
   Mat image = imread("C:/Users/revanthshetti/OneDrive/Desktop/spidey/input.bmp");


    if (image.empty()) {
        cerr << "Failed to load image. Check the path!" << endl;
        return -1;
    }

    resize_and_time(image, INTER_NEAREST, "INTER_NEAREST");
    resize_and_time(image, INTER_LINEAR, "INTER_LINEAR");
    resize_and_time(image, INTER_CUBIC, "INTER_CUBIC");

    return 0;
}
