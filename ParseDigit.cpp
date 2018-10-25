#include "ParseDigit.h"
#include <iostream>
using namespace std;
using namespace cv;

ParseDigit::ParseDigit(cv::Mat &Image) : mImage(Image) {
}

ParseDigit::~ParseDigit() {
}

vector<Rect> ParseDigit::runMSER(Mat &gray) {
	vector<vector<cv::Point> > regions;
	Ptr<MSER> ms = MSER::create(5, 30);
	vector<cv::Rect> mser_bbox;

	cout << "Parsing...";

	//detect Maximally Stable Extremal Region on the given image
	ms->detectRegions(gray, regions, mser_bbox);

    //check for overlapping rectangles and merge them
    for (auto i = mser_bbox.begin(); i != mser_bbox.end(); i++) {
			for (auto j = i+1; j != mser_bbox.end();) {
                if ((*i & *j).area() > 0) {
                    *i = *i | *j;
                    mser_bbox.erase(j);
					j = i+1;
                }
                else {
                    j++;
                }	
            }
	}

	//check for rectangles that are close and merge them 
	int minLength = min(gray.cols, gray.rows);
	for (auto i = mser_bbox.begin(); i!= mser_bbox.end(); i++) {
		for (auto j = i+1; j != mser_bbox.end();) {
			Rect rect1 = *i;
			Rect rect2 = *j;

			Point p(rect1.x + rect1.width/2, rect1.y + rect1.height/2);
			Point q(rect2.x + rect2.width/2, rect2.y + rect2.height/2);
			Point diff = p - q;

			if (sqrt(diff.x*diff.x + diff.y*diff.y) < minLength/10) {
				*i = *i | *j;
				mser_bbox.erase(j);
				j = i+1;
			}
			else {
				j++;
			}
		}
	}
	//show image with rectangles
	Mat temp = gray.clone();
    for (int i= 0; i<mser_bbox.size(); i++ ) {
        rectangle(temp, mser_bbox[i], CV_RGB(255, 255, 0));
    }
	cout << "done." << endl;
	cout << "Total " << mser_bbox.size() << " digits found. " << endl;
	imshow("mser", temp);
	waitKey(0);
	return mser_bbox;
}

// bool operator==(const Rect& rect1, const Rect& rect2)
// {
//     return (rect1.x == rect2.x) && (rect1.y == rect2.y) && (rect1.width == rect2.width) && (rect1.height == rect2.height)
// }

// unordered_map<cv::Rect, int> ParseDigit::cropImg(vector<Rect> &vec, Mat &img) {
// 	unordered_map<Rect, int> map;
// 	Mat crop;
// 	char c;
// 	int digit;
// 	for (auto itr= vec.begin(); itr!=vec.end();) {
// 		//crop the image
// 		crop = img(*itr);
// 		cout << "Is this image a digit? (y/n) : ";
// 		imshow("Crop", crop);
// 		cin >> c;
// 		switch (c) {
// 		case 'Y':
// 		case 'y':
// 			cout << "Which digit is it? (0-9) : ";
// 			cin >> digit;
// 			while (digit < 0 || digit > 10) {
// 				cout << "Please enter a valid digit (0-9) : ";
// 				cin >> digit;
// 			}
// 			map[*itr] = digit;
// 			itr++;
// 			break;
// 		case 'N':
// 		case 'n':
// 			itr++;
// 			break;
// 		default:
// 			cout << "Please indicate correct input (y/n) : ";
// 			cin >> c;
// 			break;
// 	}
// 	return map;
// }

void ParseDigit::postProcessImg(vector<Rect> &map, Mat &img) {
	Mat crop;
	Mat m = Mat::ones(2,2,CV_8U); //kernel for dilation
	int count = 0; //count for filename
	for (auto itr = map.begin(); itr!=map.end(); itr++) {
		//crop the image
		crop = img(*itr);
		
		//invert the color and resize it to 20x20
		resize(255-crop, crop, Size(20, 20));
		
		//convert to black/white image
		threshold(crop, crop, 0, 255, THRESH_OTSU);
		
		//dilate image
		dilate(crop, crop, m); 
		
		//add border to the image so that the digits will be in the center
		copyMakeBorder(crop, crop, 4, 4, 4, 4, BORDER_CONSTANT, Scalar(0,0,0));
		
		imwrite(to_string(count).append(".jpg"), crop); 
		count++;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		cout << "Usage: ./ParseDigit [input image]" << endl;
		return -1;
	}

	Mat img = imread(argv[1], IMREAD_GRAYSCALE);

	if (img.empty()) {
		cout << "Invalid image: " << argv[1] << endl;
		return -1;
	}
	resize(img, img, Size(img.cols/4, img.rows/4));
    ParseDigit target(img);
	vector<Rect> rect = target.runMSER(img);
	//unordered_map<Rect, int> map = target.cropImg(rect, img);
	target.postProcessImg(rect, img);
	return 0;
}
