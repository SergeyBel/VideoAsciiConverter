#pragma once

#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;


Vec3b GetBGRPixel(Mat image, int i, int j)
{
	return image.at<Vec3b>(i, j);
}



double GetBrightness(int red, int green, int blue)
{
	return 0.2126 * red + 0.7152 * green + 0.0722 * blue;
}

double GetBrightness(Vec3b pixel)
{
	int blue = pixel[0];
	int green = pixel[1];
	int red = pixel[2];
	return GetBrightness(red, green, blue);
}
