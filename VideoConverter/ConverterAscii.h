#pragma once

#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"
#include "SymbolsDrawer.h"

using namespace std;
using namespace cv;

class ConverterAscii
{	
	string ascii;   //string of characters for replace
	int type;    // type of image
	SymbolsDrawer drawer;  // class for draw symbols
	vector<Scalar> colors;  // color of every symbol

	char ConvertMatrixToChar(Mat matrix);
	Mat AsciiStringToAsciiImage(string  str, int height, int width);
	string ConvertImageToString(Mat image);
	void DrawAsciiLine(Mat image, int j, string line);
	Mat ResizeImage(Mat image);

public:
	ConverterAscii();
	Mat ConvertImageToAsciiImage(Mat image);
	string ConvertImageToAsciiString(Mat image);
	int GetMaxSymbolHeight();
	int GetMaxSymbolWidth();
};