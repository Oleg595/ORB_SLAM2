//
// Created by oleg on 20.10.23.
//

#include "ImagePreprocessing.h"

void CompositePreprocess::processImage(cv::Mat &img) {
    for (int index = 0; index < this->processors.size(); ++index) {
        ImagePreprocessing* proc = this->processors.data()[index];
        proc->processImage(img);
    }
}

void ResharpedFilter::processImage(cv::Mat &img) {
    cv::Mat kernel = (cv::Mat_<double>(3,3) << -1, -1, -1, -1, 9, -1, -1, -1, -1);
    cv::filter2D(img, img, -1, kernel, cv::Point(-1, -1), 0, 4);
}

void SmoothingFilter::processImage(cv::Mat &img) {
    cv::blur(img, img, cv::Size(3, 3), cv::Point(-1, -1) );
}

void MedianFilter::processImage(cv::Mat &img) {
    cv::medianBlur(img, img, 3);
}
