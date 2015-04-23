#pragma once;

#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class SymbolsDrawer
{
	string ascii;
	int fontFace;
	double fontScale;
	int thickness;
	int type;
	vector<Mat> symbolsImages;

	void SetMaxSymbolWidth();
	void SetMaxSymbolHeight();
	vector<Mat> SymbolsImages();
public:
	int maxSymbolWidth;
	int maxSymbolHeight;
	SymbolsDrawer(string ascii = "");
	void DrawAsciiLine(Mat image, int i, string line);
};