#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

int main()
{
    // Load an image
    cv::Mat image = cv::imread("../resources/aiko_test.jpg");

    // Check if the image was loaded successfully
    if (image.empty())
    {
        std::cerr << "Error loading image!" << std::endl;
        return -1;
    }

    // Display the image in a window
    cv::imshow("Display Window", image);

    // Wait for a keystroke in the window
    cv::waitKey(0);

    return 0;
}