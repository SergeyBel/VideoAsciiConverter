#include "SymbolsDrawer.h"

SymbolsDrawer::SymbolsDrawer(string ascii)
{
	fontFace = FONT_HERSHEY_SIMPLEX;
	fontScale = 1;
	thickness = 1;
	type = 16;
	this->ascii = ascii;
	SetMaxSymbolWidth();
	SetMaxSymbolHeight();
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

Mat SymbolsDrawer::GetSymbolImage(string str, Scalar color)
{
	Mat m(maxSymbolHeight, maxSymbolWidth, type);
	m = Mat::zeros(maxSymbolHeight, maxSymbolWidth, type);
	Point org = Point(0, maxSymbolHeight - 1);
	//cout << "FontScale = " << fontScale << endl;
	putText(m, str, org, fontFace, fontScale, color);
	return m;

}

void SymbolsDrawer::DrawAsciiLine(Mat image, int i, string line, vector<Scalar> lineColors)
{
	int j = 0;
	for (int k = 0; k < line.length(); k++)
	{
		Mat tmp = image(Rect(j, i, maxSymbolWidth, maxSymbolHeight));
		GetSymbolImage(line.substr(k, 1), lineColors[k]).copyTo(tmp);
		j += maxSymbolWidth;
	}
}

void SymbolsDrawer::SetFontScale(double scale)
{
	this->fontScale = scale;
	SetMaxSymbolWidth();
	SetMaxSymbolHeight();

}
