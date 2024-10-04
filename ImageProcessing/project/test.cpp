#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Open the default camera (camera index 0)
    cv::VideoCapture cap(0);

    // Check if the camera opened successfully
    if (!cap.isOpened()) {
        std::cout << "Error: Could not open camera" << std::endl;
        return -1;
    }

    // Create a window to display the video stream
    cv::namedWindow("Camera Stream", cv::WINDOW_AUTOSIZE);

    while (true) {
        // Create a matrix to store the camera frame
        cv::Mat frame;

        // Capture the frame from the camera
        cap >> frame;

        // Check if the frame is empty (i.e., if there's an issue capturing)
        if (frame.empty()) {
            std::cout << "Error: Could not retrieve frame" << std::endl;
            break;
        }

        // Display the frame in the window
        cv::imshow("Camera Stream", frame);

        // Wait for 1ms and check if the user pressed the 'q' key
        // Exit the loop if 'q' is pressed
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // Release the camera once done
    cap.release();

    // Close all OpenCV windows
    cv::destroyAllWindows();

    return 0;
}
