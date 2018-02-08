#include "opencv2/objdetect.hpp"
#include "opencv2/opencv.hpp"
#include <fstream>

using namespace cv;
using namespace std;

// Laser color
int sensitivity = 90;
const Scalar lColor(60 - sensitivity, 100, 50);  // lower bound
const Scalar hColor(60 + sensitivity, 255, 255); // upper bound

int main() {
    VideoCapture capture;

    Mat frame;
    Mat colorized;
    Mat HSV;
    Mat mask;
    Mat eroded;

    const double stickSpace = 100;
    double distance;
    int toolState = 0;
    Point point(-100, -100);

    int actionNumber = 0;

    string path = __FILE__;
    path.erase(path.length() - 8);

    ofstream fout(path + "/test.gcode");                    //  |
    fout << "%\n";                                          //  |- Setup G-code file
    fout << "G90 G40 G17\n";                                //  |

    capture.open(0);
    if (!capture.isOpened()) {
        cout << "Cannot open video stream";
    }

    while (true) {
        capture.read(frame);


        frame.convertTo(colorized, CV_8UC1, 0.4, 0);
//        imshow("colorized", colorized);
        cvtColor(colorized, HSV, CV_BGR2HSV);
        inRange(HSV, lColor, hColor, mask);

//        imshow("dirty", mask);
        erode(mask, mask, Mat(), Point(-1, -1), 2, 1, 1);   //   |
        dilate(mask, mask, Mat(), Point(-1, -1), 1, 1, 1);  //   |- Cleaning ang blurring
        GaussianBlur(mask, mask, cv::Size(7, 7), 2, 2);     //   |
//        imshow("clean", mask);

        vector<Vec3f> circles;

        HoughCircles(mask, circles, CV_HOUGH_GRADIENT, 1, frame.size().width/8, 100, 10, 15, 100);

        if (circles.size() > 0) {
            for (size_t currentCircle = 0; currentCircle < circles.size(); ++currentCircle) {
                Point center(round(circles[currentCircle][0]), round(circles[currentCircle][1]));
                int radius = round(circles[currentCircle][2]);

                cout << center << "\n";
                circle(frame, center, radius, Scalar(0, 0, 255), 5);

                distance = norm(point-center);

                if (distance < stickSpace) {
                    fout << "G01" << " X" << circles[currentCircle][0] << " Y" << circles[currentCircle][1] << "\n";
                } else {
                    if (toolState == -1) fout << "G00 Z1\n";
                    fout << "G00" << " X" << circles[currentCircle][0] << " Y" << circles[currentCircle][1] << "\n";
                    fout << "G00 Z-1.0\n";
                    toolState = -1;
                }
            }
        }

        imshow("orig", frame);

        if (waitKey(30) == 27) {
            fout << "G00 Z0.0\n";
            fout << "G00 X0.0 Y0.0\n";
            fout << "M02\n";
            break;
        }
    }


    return 0;
}