#include <opencv2/videoio.hpp>
#include <opencv/cv.hpp>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace std;
using namespace cv;


int edgeFromCamera() {
    VideoCapture cap(0);
    if(!cap.isOpened())
        return -1;

    Mat edges;
    namedWindow("edges",1);
    for(;;) {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, CV_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        blur(edges, edges, Size(7,7));
        //Sobel(edges,edges,edges.depth(),1,0,3);
        Canny(edges, edges, 0, 30, 3);
        imshow("edges", edges);
        if(cv::waitKey(30) >= 0) break;
    }
    return 0;
}







int edgePhoto() {
    //VideoCapture cap(0);

    //if(!cap.isOpened())
      //  return -1;

    Mat edges ;
    namedWindow("edges",1);

    for(;;) {
        Mat frame = imread(
                "/Users/lucky.mz/Documents/GitHub/RSE_lirs/img/left3.jpg",1
        );
        //cap >> frame; // get a new frame from camera
        cvtColor(frame, edges,CV_BGR2GRAY);

        //bilateralFilter(edges, edges,10,10*2,10*2);




        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        //blur(edges,edges,Size(7,7));
        //medianBlur( edges, edges, 7);

        //fastNlMeansDenoisingColored(edges,edges,3,3,7,21);
        //cvtColor(edges, edges,CV_BGR2GRAY);


        Sobel(edges,edges,edges.depth(),1,0);

        //Canny(edges, edges, 0, 30, 3);

        imshow("edges", edges);
        if(waitKey(30) >= 0) break;
    }
    return 0;
}

