#include "opencv2/opencv.hpp"
#include <fstream>
#include "ConverterAscii.h"
using namespace cv;
using namespace std;



int main(int, char**)
{
    VideoCapture cap("video.avi"); // open the default camera
    if (!cap.isOpened())// check if we succeeded
    {
        cout << "Error: Can not open file" << endl;
        return -1;
    }
        
    Mat edges;
    namedWindow("edges", CV_WINDOW_AUTOSIZE);
    cap.set(CV_CAP_PROP_POS_MSEC, 1000 * 1000);
    ConverterAscii converter;
    for (;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        imshow("frame", frame);
        if (waitKey(30) >= 0) break;
        cvtColor(frame, edges, 0);
        edges = converter.ConvertImageToAsciiImage(edges);;
        imshow("edges", edges);
       // if (waitKey(30) >= 0) break;
    }


    ///Test case
    /*
    ConverterAscii converter;
    Mat image;
    ofstream out("log.txt");
    image = imread("image.jpg", CV_LOAD_IMAGE_COLOR);

    imshow("1", image);
    waitKey(20);
    cout << converter.ConvertImageToAsciiString(image) << endl;
    converter.ConvertImageToAsciiImage(image);
    out.close();
    */
    return 0;
}