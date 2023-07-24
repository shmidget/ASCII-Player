#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if (!cap.isOpened())  // check if we succeeded
        return -1;

    Ptr<BackgroundSubtractor> pMOG = new BackgroundSubtractorMOG2();

    Mat fg_mask;
    Mat frame;
    int count = -1;

    for (;;)
    {
        // Get frame
        cap >> frame; // get a new frame from camera

        // Update counter
        ++count;

        // Background subtraction
        pMOG->operator()(frame, fg_mask);

        imshow("frame", frame);
        imshow("fg_mask", fg_mask);

        // Save foreground mask
        std::string name = "mask_" + std::to_string(count) + ".png";
        imwrite("D:\\SO\\temp\\" + name, fg_mask);

        if (waitKey(1) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}