//
// Created by oleg on 20.10.23.
//

#ifndef ORB_SLAM2_IMAGEPREPROCESSING_H
#define ORB_SLAM2_IMAGEPREPROCESSING_H

#include<opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class ImagePreprocessing {
public:
    virtual void processImage(cv::Mat &image) = 0;
    virtual std::string getClassName() = 0;
};

class CompositePreprocess : public ImagePreprocessing {
private:
    std::vector<ImagePreprocessing*> processors;
public:
    CompositePreprocess(std::vector<ImagePreprocessing*> procs) {
        processors = std::vector<ImagePreprocessing*>();
        for (int index = 0; index < procs.size(); ++index) {
            processors.push_back(procs.data()[index]);
        }
    }
    void processImage(cv::Mat &img) override;
    std::string getClassName() override {
        return "CompositePreprocess";
    }
};

class ResharpedFilter : public ImagePreprocessing {
public:
    void processImage(cv::Mat &img) override;
    std::string getClassName() override {
        return "ConvolutionalFiltering";
    }
};

class SmoothingFilter : public ImagePreprocessing {
public:
    void processImage(cv::Mat &img) override;
    std::string getClassName() override {
        return "SmoothingFilter";
    }
};

class MedianFilter : public ImagePreprocessing {
public:
    void processImage(cv::Mat &img) override;
    std::string getClassName() override {
        return "MedianFilter";
    }
};

ImagePreprocessing * getCurrentPreprocessing() {
    return new MedianFilter();
}

#endif //ORB_SLAM2_IMAGEPREPROCESSING_H
