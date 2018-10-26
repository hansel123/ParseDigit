# AMD ParseDigit

The AMD ParseDigit is a useful tool for preparing image dataset for [MNIST](http://yann.lecun.com/exdb/mnist/). 
The program will automatically detect digits from the input image, crop, and preprocess the images.

### Explanation
The program uses opencv [MSER function](https://docs.opencv.org/3.1.0/d3/d28/classcv_1_1MSER.html) for detecting digits.
After detecting and cropping the images, it preprocesses the images so that it can be used for MNIST dataset.
The detailed explanation of preprocessing the images can be found at http://opensourc.es/blog/tensorflow-mnist


### Pre-requisites
##### 1. OpenCV 3.1 [download](https://opencv.org/opencv-3-1.html) or higher
##### 2. cmake git 
    sudo apt-get install cmake git

### Build using Cmake on Linux (Ubuntu 16.04 64bit)
     git clone https://github.com/hansely/ParseDigit.git
     cd ParseDigit
     mkdir build
     cd build
     cmake ..
     make

### Usage
     Usage: ./ParseDigit [input_image] [image_name] [-a]
     
     1. [input_image]
         The name of the input image (including the directory to the image) to run the detection and crop.
     2. [image_name]
         The name of the ouput images (including the directory to the image).
         The name of the images will be "[image_name]00[digit]-[digit count].jpg".
         If -a option is set, the names will be "[image_name]001.jpg", "[image_name]002.jpg" ... and so on.
     3. [-a]
         If -a option is set, it will skip the digit verification process and automatically name the images 
         as mentioned above. Otherwise, it will show each detected digits and go through verification process.
       
### Example
    ./ParseDigit ../Examples/image.jpg ../Examples/Cropped/digits
    
    The output images will be stored in ../Examples/Cropped folder as digits001-1.jpg, digits001-2.jpg, ... digits009-5.jpg.
    Make sure the destination folder is created before running the program.
