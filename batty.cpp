#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

using namespace std;
using namespace cv;
using namespace std::chrono;

// ==============================
// NEAREST NEIGHBOR INTERPOLATION
// ==============================
void custom_resize_nearest(const Mat& src, Mat& dst, int new_width, int new_height) {
    dst = Mat(new_height, new_width, src.type());
    float x_ratio = (float)src.cols / new_width;
    float y_ratio = (float)src.rows / new_height;

    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            int px = floor(j * x_ratio);
            int py = floor(i * y_ratio);
            dst.at<Vec3b>(i, j) = src.at<Vec3b>(py, px);
        }
    }
}

// ============================
// BILINEAR INTERPOLATION
// ============================
void custom_resize_linear(const Mat& src, Mat& dst, int new_width, int new_height) {
    dst = Mat(new_height, new_width, src.type());
    float x_ratio = (float)(src.cols - 1) / new_width;
    float y_ratio = (float)(src.rows - 1) / new_height;

    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            float x = x_ratio * j;
            float y = y_ratio * i;

            int x_l = (int)x;
            int y_l = (int)y;
            int x_h = min(x_l + 1, src.cols - 1);
            int y_h = min(y_l + 1, src.rows - 1);

            float x_diff = x - x_l;
            float y_diff = y - y_l;

            for (int c = 0; c < 3; c++) {
                float A = src.at<Vec3b>(y_l, x_l)[c];
                float B = src.at<Vec3b>(y_l, x_h)[c];
                float C = src.at<Vec3b>(y_h, x_l)[c];
                float D = src.at<Vec3b>(y_h, x_h)[c];

                float pixel = A * (1 - x_diff) * (1 - y_diff) +
                              B * x_diff * (1 - y_diff) +
                              C * (1 - x_diff) * y_diff +
                              D * x_diff * y_diff;

                dst.at<Vec3b>(i, j)[c] = (uchar)pixel;
            }
        }
    }
}
float cubic_interp(float v0, float v1, float v2, float v3, float x) {
    return v1 + 0.5f * x * (v2 - v0 + x * (2.0f * v0 - 5.0f * v1 + 4.0f * v2 - v3 + x * (3.0f * (v1 - v2) + v3 - v0)));
}

void custom_resize_cubic(const Mat& src, Mat& dst, int new_width, int new_height) {
    dst = Mat(new_height, new_width, src.type());
    float x_ratio = (float)(src.cols) / new_width;
    float y_ratio = (float)(src.rows) / new_height;

    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            float x = x_ratio * j - 0.5f;
            float y = y_ratio * i - 0.5f;

            int x_int = floor(x);
            int y_int = floor(y);

            for (int c = 0; c < 3; ++c) {
                float patch[4][4];

                for (int m = -1; m <= 2; ++m) {
                    for (int n = -1; n <= 2; ++n) {
                        int px = std::clamp(x_int + n, 0, src.cols - 1);
                        int py = std::clamp(y_int + m, 0, src.rows - 1);
                        patch[m + 1][n + 1] = src.at<Vec3b>(py, px)[c];
                    }
                }

                float col[4];
                for (int m = 0; m < 4; ++m) {
                    col[m] = cubic_interp(patch[m][0], patch[m][1], patch[m][2], patch[m][3], x - x_int);
                }

                float value = cubic_interp(col[0], col[1], col[2], col[3], y - y_int);
                dst.at<Vec3b>(i, j)[c] = saturate_cast<uchar>(value);
            }
        }
    }
}

// ============================
// TIMING + COMPARISON
// ============================
void run_custom_resize(const Mat& image, const string& method) {
    int new_w = image.cols / 2;
    int new_h = image.rows / 2;
    Mat result;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
        if (method == "INTER_NEAREST") {
            custom_resize_nearest(image, result, new_w, new_h);
        } else if (method == "INTER_LINEAR") {
            custom_resize_linear(image, result, new_w, new_h);
        }else if (method == "INTER_CUBIC") {
            custom_resize_cubic(image, result, new_w, new_h);
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    cout << "⏱️ Custom resize [" << method << "]: " << duration << " ms" << endl;

    imwrite("custom_" + method + ".bmp", result);
    // imshow("Custom - " + method, result);
}

// ============================
// MAIN
// ============================
// int main() {
//     Mat image = imread("C:/Users/revanthshetti/OneDrive/Desktop/spidey/input.bmp"); // Replace with your image path

//     if (image.empty()) {
//         cerr << "❌ Failed to load image." << endl;
//         return -1;
//     }

//     cout << "✅ Image loaded. Starting custom resizing...\n";

//     imshow("Original", image);
//     run_custom_resize(image, "INTER_NEAREST");
//     run_custom_resize(image, "INTER_LINEAR");

//     cout << "✅ Done. Press any key to close windows." << endl;
//     waitKey(0);
//     destroyAllWindows();
//     return 0;
// }
int main() {
    // cout << "🚀 Program started..." << endl;

    Mat image = imread("C:/Users/revanthshetti/OneDrive/Desktop/spidey/input.bmp");

    if (image.empty()) {
        cerr << "❌ Failed to load image. Check the path!" << endl;
        return -1;
    }

    // cout << "✅ Image loaded successfully.\n";

    // imshow("Original Image", image);

    run_custom_resize(image, "INTER_NEAREST");
    run_custom_resize(image, "INTER_LINEAR");
    run_custom_resize(image, "INTER_CUBIC");

    // cout << "✅ All custom resizing done. Press any key to close windows." << endl;

    // waitKey(0);
    // destroyAllWindows();
    return 0;
}


