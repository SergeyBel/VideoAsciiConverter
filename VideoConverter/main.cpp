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
    h = h + (converter.GetDrawer().maxSymbolHeight - h % converter.GetDrawer().maxSymbolHeight);
    w = w + (converter.GetDrawer().maxSymbolWidth - w % converter.GetDrawer().maxSymbolWidth);

    VideoWriter outputVideo;    // Open the output
    outputVideo.open(name, ex = -1, inputVideo.get(CV_CAP_PROP_FPS), Size(w, h), true);

    if (!outputVideo.isOpened())
    {
        cout << "Could not open the output video for write: " << endl;
        return -1;
    }
    
    cout << "Input frame resolution: Width=" << w << "  Height=" << h
        << " of nr#: " << inputVideo.get(CV_CAP_PROP_FRAME_COUNT) << endl;
    cout << "Input codec type: " << EXT << endl;



    Mat edges;
    namedWindow("edges", CV_WINDOW_AUTOSIZE);
    inputVideo.set(CV_CAP_PROP_POS_MSEC, 1000 * 2000);

    for (;;)
    {
        Mat frame;
        inputVideo >> frame; // get a new frame from camera
        if (frame.empty()) break;  // end of file
        imshow("frame", frame);
        if (waitKey(30) >= 0) break;
        edges = converter.ConvertImageToAsciiImage(frame);
        imshow("edges", edges);
        outputVideo << edges;
        if (inputVideo.get(CV_CAP_PROP_POS_MSEC) >= 1000 * 2000 + 10 * 1000) return 0;
    }
    return 0;
}