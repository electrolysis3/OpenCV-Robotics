#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Open a connection to the default webcam (camera index 0)
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open the webcam!" << std::endl;
        return -1;
    }

    cv::Mat frame, gray_frame, blurred_frame, laplacian, abs_laplacian, enhanced_edges;

    while (true) {
        // Capture each frame from the webcam
        cap >> frame;

        if (frame.empty()) {
            std::cerr << "Error: Could not capture frame!" << std::endl;
            break;
        }

        // Step 1: Convert the frame to grayscale
        cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);

        // Step 2: Apply Gaussian Blur to reduce noise
        cv::GaussianBlur(gray_frame, blurred_frame, cv::Size(3, 3), 0);

        // Step 3: Apply the Laplacian operator to detect edges
        cv::Laplacian(blurred_frame, laplacian, CV_16S, 3);

        // Step 4: Convert back to CV_8U type for proper display
        cv::convertScaleAbs(laplacian, abs_laplacian);

        // Step 5: Enhance the edges by scaling up the intensity (brighter edges)
        abs_laplacian.convertTo(enhanced_edges, -1, 2.0, 0); // Multiply pixel values by 2 for brightness

        // Step 6: Display the original and the edge-detected images
        cv::imshow("Webcam Feed", frame);
        cv::imshow("Laplacian of Gaussian Edge Detection", enhanced_edges);

        // Break the loop if the 'q' key is pressed
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }

    // Release the webcam and close windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
