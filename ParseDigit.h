#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/features2d/features2d.hpp"
#include <vector>
//#include <unordered_map>

class ParseDigit {
	
public:

	ParseDigit(cv::Mat &image);

	~ParseDigit();

    /**
	 Crop the input image according to the given rectangle info and preprocess it.
	 */
	void postProcessImg(std::vector<cv::Rect> &map, cv::Mat &img);

	/**
	 Crop the input image according to the given rectangle info and preprocess it.
	 */
//	std::unordered_map<cv::Rect, int> cropImg(std::vector<cv::Rect> &vec, cv::Mat &img);
 	
	/**
	 Run MSER function on the given grayscale image
	 */
	std::vector<cv::Rect> runMSER(cv::Mat &gray);


private:
    cv::Mat mImage;
};
