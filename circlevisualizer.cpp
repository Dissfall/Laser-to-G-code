#include "circlevisualizer.h"

CircleVisualizer::CircleVisualizer(QWidget *parent)
{

}

void CircleVisualizer::process(cv::Mat frame, std::vector<cv::Vec3f> circles)
{
    if (circles.size() > 0) {
        for (size_t currentCircle = 0; currentCircle < circles.size(); ++currentCircle) {
            cv::Point center(round(circles[currentCircle][0]), round(circles[currentCircle][1]));
            int radius = round(circles[currentCircle][2]);

            cv::circle(frame, center, radius, cv::Scalar(0, 0, 255), 5);
        }
        emit matReady(frame);
    } else {
        emit matReady(frame);
    }
}

void CircleVisualizer::processFrame(const cv::Mat &frame, const std::vector<cv::Vec3f> &circles)
{
    process(frame, circles);
}
