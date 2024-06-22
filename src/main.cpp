#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // RTSP stream URL
    std::string rtsp_url = "rtsp://192.168.1.206:8554/mjpeg/1";

    // Open the RTSP stream
    cv::VideoCapture cap(rtsp_url);

    // Check if the stream is opened successfully
    if (!cap.isOpened()) {
        std::cerr << "Error: Couldn't open the RTSP stream." << std::endl;
        return -1;
    }

    // Main loop to read frames from the RTSP stream
    cv::Mat frame;
    while (true) {
        // Read a frame
        cap >> frame;

        // Check if the frame is empty
        if (frame.empty()) {
            std::cerr << "Error: Frame is empty." << std::endl;
            break;
        }

        // Display the frame (optional)
        cv::imshow("RTSP Stream", frame);

        // Wait for a key press, break the loop if 'q' is pressed
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // Release the VideoCapture object and close the OpenCV windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
