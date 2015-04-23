#include "ConverterAscii.h"
#include "Common.h"


ConverterAscii::ConverterAscii()
{
	ascii = " .,-:;i1tfLCG08@";
	type = 16;
	drawer = SymbolsDrawer(ascii);
}


Mat ConverterAscii::ResizeImage(Mat image)
{
	int newImageHeight = image.rows + (drawer.maxSymbolHeight - image.rows % drawer.maxSymbolHeight);
	int newImageWidth = image.cols + (drawer.maxSymbolWidth - image.cols % drawer.maxSymbolWidth);
	resize(image, image, Size(newImageWidth, newImageHeight));
	return image;
}



string ConverterAscii::ConvertImageToString(Mat image)
{
	int verticalStep = drawer.maxSymbolHeight;
	int horizontalStep = drawer.maxSymbolWidth;
	string symbol;
	string resultString = "";

	for (int i = 0; i < image.rows; i += verticalStep)
	{
		string line = "";
		for (int j = 0; j < image.cols; j += horizontalStep)
		{
			Mat tmp = image(Rect(j, i, horizontalStep, verticalStep));
			Mat subm(tmp);
			symbol = ConvertMatrixToChar(subm);
			line += symbol;
		}
		line += "\n";
		resultString += line;
	}
	return resultString;
}



Mat ConverterAscii::AsciiStringToAsciiImage(string  str, int height, int width)
{
	int start = 0;
	int index = 0;
	int currentX = 0;
	int currentY = 0;
	Point org;
	Scalar color = Scalar::all(255);
	Mat res(height, width, 16);
	while ((index = str.find('\n', start)) != -1)
	{
		string line = str.substr(start, index - start);
		start = index + 1;
		//org = Point(0, currentY + maxSymbolHeight);
		//putText(res, line, org, fontFace, fontScale, color);
		drawer.DrawAsciiLine(res, currentY, line);
		currentY += drawer.maxSymbolHeight;
	}
	//namedWindow("ascii", CV_WINDOW_AUTOSIZE);
	//imshow("ascii", res);
	//waitKey(0);
	return res;
}

Mat ConverterAscii::ConvertImageToAsciiImage(Mat image)
{
	image = ResizeImage(image);
	return AsciiStringToAsciiImage(ConvertImageToString(image), image.rows, image.cols);  // *3 - for testing

}

string ConverterAscii::ConvertImageToAsciiString(Mat image)
{
	image = ResizeImage(image);
	return ConvertImageToString(image);

}

char ConverterAscii::ConvertMatrixToChar(Mat matrix)
{
	double bright = 0;
	for (int i = 0; i < matrix.rows; i++)
	{
		for (int j = 0; j < matrix.cols; j++)
		{
			Vec3b pixel = GetBGRPixel(matrix, i, j);
			bright += GetBrightness(pixel);
		}
	}


	bright /= (matrix.rows * matrix.cols);

	int index = bright / ascii.length();
	return ascii[index];
}

SymbolsDrawer ConverterAscii::GetDrawer()
{
	return drawer;
}