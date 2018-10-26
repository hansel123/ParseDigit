#include "ParseDigit.h"
#include "MSERDetector.h"
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
	if (argc < 3) {
		cout << "Usage: ./ParseDigit [input image] [image name] [-a]" << endl;
		return -1;
	}

	string inputName = argv[1];
	string targetName = argv[2];

//	resize(img, img, Size(img.cols/4, img.rows/4));
    ParseDigit parse(inputName, targetName);
	parse.run();
	return 0;
}
