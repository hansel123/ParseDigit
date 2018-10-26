#pragma once

#include "MSERDetector.h"
#include <memory>

/**
 * Custom hash function for unordered_map (Rect)
 */
struct CustomHash {
	std::size_t operator()(const cv::Rect& r) const {
		return r.x ^ r.y ^ r.width ^ r.height;	
	}
};

class ParseDigit {
	
public:

	ParseDigit(const std::string imageName, const std::string targetName);

	~ParseDigit();
 	
	/**
	 * Run detect MSER on the given grayscale image
	 */
	std::vector<cv::Rect> detectMSER();

	/**
	 * Crop the input image according to the given rectangle info and preprocess it.
	 */
	std::unordered_map<cv::Rect, std::string, CustomHash> cropImg(std::vector<cv::Rect> &mser_bbox);

    /**
	 * Crop the input image according to the given rectangle info and preprocess it.
	 */
	void postProcessImg(std::unordered_map<cv::Rect, std::string, CustomHash> &rectMap);

	/**
	 * Run Parse Digit
	 */
	void run();

private:
	/**
	 * Stores original image
	 */
    cv::Mat mOrigImage;
	
	/**
	 * Stores gray image for MSER
	 */
	cv::Mat mGrayImage;

	/**
	 * Stores name of the original image
	 */
	const std::string mImageName;

	/**
	 * Stores name of the target image
	 */
	const std::string mTargetName;

	/**
	 * MSER Detector
	 */
	std::unique_ptr<MSERDetector> mDetector;
};
