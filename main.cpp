#include "ParseDigit.h"
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
	if (argc < 3) {
		cout << "Usage: ./ParseDigit [input_image] [image_name] [-a]" << endl;
		return -1;
	}

	string inputName = argv[1];
	string targetName = argv[2];
    bool automate = false;
    if (argc == 4) {
        string option = argv[3];
        if (option == "-a") {
            automate = true;
        }
    }
    ParseDigit parse(inputName, targetName, automate);
	parse.run();
	return 0;
}
