#pragma once

#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"
#include "SymbolsDrawer.h"

using namespace std;
using namespace cv;

class ConverterAscii
{	
	string ascii;
	int type;
	SymbolsDrawer drawer;
	vector<Scalar> colors;

	char ConvertMatrixToChar(Mat matrix);

	Mat AsciiStringToAsciiImage(string  str, int height, int width);
	string ConvertImageToString(Mat image);
	void DrawAsciiLine(Mat image, int j, string line);
	Mat ResizeImage(Mat image);

public:
	ConverterAscii();
	Mat ConvertImageToAsciiImage(Mat image);
	string ConvertImageToAsciiString(Mat image);
	SymbolsDrawer GetDrawer();


};