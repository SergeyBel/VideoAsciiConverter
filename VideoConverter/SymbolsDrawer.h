#pragma once;

#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class SymbolsDrawer
{
	string ascii;  // string of symbols to dra
	int fontFace;  // font
	double fontScale;  // scale of font
	int thickness;   // thick of font line
	int type;      // type of image
	vector<Mat> symbolsImages;  // image of every symbol from ascii

	void SetMaxSymbolWidth();
	void SetMaxSymbolHeight();
	vector<Mat> SymbolsImages();
	Mat GetSymbolImage(string str, Scalar color);
public:
	int maxSymbolWidth;
	int maxSymbolHeight;
	SymbolsDrawer(string ascii = "");
	void DrawAsciiLine(Mat image, int i, string line, vector<Scalar> lineColors);
};