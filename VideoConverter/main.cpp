#include "opencv2/opencv.hpp"
#include <fstream>
#include "ConverterAscii.h"
using namespace cv;
using namespace std;



int main(int, char**)
{
    ConverterAscii converter;
    VideoCapture inputVideo("video.avi"); // open the default camera
    if (!inputVideo.isOpened())// check if we succeeded
    {
        cout << "Error: Can not open input video" << endl;
        return -1;
    }

    string name = "out.avi";
    int ex = static_cast<int>(inputVideo.get(CV_CAP_PROP_FOURCC));     // Get Codec Type- Int form

    // Transform from int to char via Bitwise operators
    char EXT[] = { (char)(ex & 0XFF), (char)((ex & 0XFF00) >> 8), (char)((ex & 0XFF0000) >> 16), (char)((ex & 0XFF000000) >> 24), 0 };


    int h = inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT);
    int w = inputVideo.get(CV_CAP_PROP_FRAME_WIDTH);
    h = h + (converter.GetMaxSymbolHeight() - h % converter.GetMaxSymbolHeight());  // image size should be whole number of symbols
    w = w + (converter.GetMaxSymbolWidth() - w % converter.GetMaxSymbolWidth());

    VideoWriter outputVideo;    // Open the output
    outputVideo.open(name, ex = -1, inputVideo.get(CV_CAP_PROP_FPS), Size(w, h), true);

    if (!outputVideo.isOpened())
    {
        cout << "Could not open the output video for write: " << endl;
        return -1;
    }
    
    cout << "Input frame resolution: Width=" << w << "  Height=" << h
        << "number of frames: " << inputVideo.get(CV_CAP_PROP_FRAME_COUNT) << endl;
    cout << "Input codec type: " << EXT << endl;



    Mat asciiFrame;
    long long frames = 1;
    int oldPercent = 0;
    cout << "Start rendering" << endl;
    for (;;)
    {
        Mat frame;
        inputVideo >> frame; // get a new frame from video
        if (frame.empty()) break;  // end of file
        asciiFrame = converter.ConvertImageToAsciiImage(frame);
        outputVideo << asciiFrame;
        double percent = frames / (double)inputVideo.get(CV_CAP_PROP_FRAME_COUNT)  * 100;
        if (percent - oldPercent > 1)
        {
            oldPercent = std::floor(percent);
            cout << oldPercent << " % rendered..." << endl;
        }
        frames++;
    }
    cout << "End rendering" << endl;
    return 0;
}