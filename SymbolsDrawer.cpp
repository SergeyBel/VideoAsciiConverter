#include "SymbolsDrawer.h"

SymbolsDrawer::SymbolsDrawer(string ascii)
{
	fontFace = FONT_HERSHEY_SIMPLEX;
	fontScale = 0.07;
	thickness = 1;
	type = 16;
	this->ascii = ascii;
	SetMaxSymbolWidth();
	SetMaxSymbolHeight();
	symbolsImages = SymbolsImages();
}


void SymbolsDrawer::SetMaxSymbolWidth()
{
	int baseLine = 0;
	int max = 0;
	for (int i = 0; i < ascii.length(); i++)
	{
		max = std::max(getTextSize(ascii.substr(i, 1), fontFace, fontScale, thickness, &baseLine).width, max);
	}
	maxSymbolWidth = max;
}

void  SymbolsDrawer::SetMaxSymbolHeight()
{
	int baseLine = 0;
	int max = 0;
	for (int i = 0; i < ascii.length(); i++)
	{
		max = std::max(getTextSize(ascii.substr(i, 1), fontFace, fontScale, thickness, &baseLine).height, max);
	}
	maxSymbolHeight = max + 1;
}


vector<Mat>  SymbolsDrawer::SymbolsImages()
{
	vector<Mat> result;
	int baseLine = 0;
	Point org(0, maxSymbolHeight);
	Scalar color = Scalar::all(255);
	for (int i = 0; i < ascii.length(); i++)
	{
		Mat m(maxSymbolHeight, maxSymbolWidth, type);
		m = Mat::zeros(maxSymbolHeight, maxSymbolWidth, type);
		org = Point(0, maxSymbolHeight - 1);
		putText(m, ascii.substr(i, 1), org, fontFace, fontScale, color);
		result.push_back(m);
	}
	return result;
}

void SymbolsDrawer::DrawAsciiLine(Mat image, int i, string line)
{
	int j = 0;
	for (int k = 0; k < line.length(); k++)
	{
		Mat tmp = image(Rect(j, i, maxSymbolWidth, maxSymbolHeight));
		int index = ascii.find(line[k]);
		symbolsImages[index].copyTo(tmp);
		j += maxSymbolWidth;
	}
}
