#include <iostream>
#include <string>



#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv/cv.hpp>


using namespace cv;
using namespace std;


//Mat frame;
//auto calibMatrix;
//auto distrCoefs;
Size size(744,480);

double stereo_kr_data[3][3] = { {339.235023,0.000000,361.816561},
                                {0.000000,339.854855,298.800560},
                                {0.000000,0.000000,1.000000} };
double stereo_dr_data[1][5] =  {-0.227741, 0.040889, -0.001854, 0.001510, 0.000000};
double stereo_rr_data[3][3] = { {0.999910, 0.001597, -0.013296},
                                {-0.001650, 0.999991, -0.003962},
                                {0.013290, 0.003984, 0.999904} };
double stereo_pr_data[3][4] = {
        {403.605939, 0.000000, 324.601709, 0.000000},
        {0.000000, 403.605939, 249.747250, 0.000000},
        {0.000000, 0.000000, 1.000000, 0.000000}
};

double stereo_kl_data[3][3] = {
        {345.107292, 0.000000, 379.543780},
        {0.000000, 351.947433, 202.905149},
        {0.000000, 0.000000, 1.000000}
};
double stereo_dl_data[1][5] =  {-0.225886, 0.043241, 0.003057, -0.005799,0.000000};
double stereo_rl_data[3][3] = {
        {0.991289, -0.001251, 0.131698,},
        {0.000727, 0.999992, 0.004030},
        {-0.131702, -0.003899, 0.991282}
};
double stereo_pl_data[3][4] = {
        {403.605939, 0.000000, 324.601709, 87.522023},
        {0.000000, 403.605939, 249.747250, 0.000000},
        {0.000000, 0.000000, 1.000000, 0.000000}
};

double k_left[3][3] = {
        {380.3217282767636, 0, 371.9700389924079 },
        {0, 380.3952128325561, 292.1186168515914},
        {0, 0, 1}
};
double d_left[1][5] =  {-0.2906326337537663, 0.06863818943326856, -0.001780005171518453, 0.0008870990677500119, 0};
double r_left[3][3] = {
        {1, 0, 0},
        {0,1,0},
        {0,0,1}
};
double p_left[3][4] = {
        {264.5990905761719, 0, 371.3741814505338, 0},
        {0, 324.8956604003906, 308.9112011065263, 0},
        { 0, 0, 1, 0}
};
///////////////////////////////////////////////////////////
/** cout << "m = " << endl << " " << D1 << endl << endl;

    string filename2 = "right.yaml";
    FileStorage fs;
    fs.open(filename2, FileStorage::READ);
    fs["image_width"] >> dist_model2;
    fs["camera_matrix"] >> K2;
    fs["distortion_model"] >> dist_model2;
    fs["distortion_coefficients"] >> D2;
    fs["rectification_matrix"] >> R2;
    fs["projection_matrix"] >> P2;
    fs.release();
////////////////////////////////////////////////////////////////////////*/


void undistorting(Mat &imgL, Mat &imgR){

    Mat imgUndistortedR(imgR.size(),imgR.type());
    Mat imgUndistortedL(imgL.size(),imgL.type());

    Mat KL(3,3,CV_64F,stereo_kl_data);
    Mat DL(1,5,CV_64F,stereo_dl_data);
    Mat RL(3,3,CV_64F,stereo_rl_data);
    Mat PL(3,4,CV_64F,stereo_pl_data);
    cvtColor(imgL, imgL, CV_BGR2GRAY);

    undistort(imgL,imgUndistortedL,KL,DL,PL);
    //imshow("left", imgUndistortedL);
    imgL = imgUndistortedL.clone();

    Mat chg;


    Mat KR(3,3,CV_64F,stereo_kr_data);
    Mat DR(1,5,CV_64F,stereo_dr_data);
    Mat RR(3,3,CV_64F,stereo_rr_data);
    Mat PR(3,4,CV_64F,stereo_pr_data);
    cvtColor(imgR, imgR, CV_RGB2GRAY,2);


    undistort(imgR,imgUndistortedR,KR,DR,PR);
    //imgR = imgUndistortedR.clone();

    //fisheye::undistortPoints(imgR,imgUndistortedR,KR,DR,PR,RR);
    //fisheye::undistortImage(imgR,imgUndistortedR,KR,DR,PR);
    imgR = imgUndistortedR.clone();

    imshow("right", imgR);
    waitKey(0);


}



void calib_img(){
    //calibrateCamera(frame,frame,Size(744,480),calibMatrix,distrCoefs);

    Mat imgL = imread("../img/left3.jpg");
    Mat imgR = imread("../img/right3.jpg");


    Mat disp, disp8;


    undistorting(imgL,imgR);
    //cout << imgL.size() << imgR.size() << endl;


    Ptr<StereoSGBM> sgbm = StereoSGBM::create();
    sgbm->compute(imgL,imgR,disp);



    Ptr<StereoBM> sbm = cv::StereoBM::create(16, 5);

    sbm->setDisp12MaxDiff(1);
    sbm->setSpeckleRange(8);
    sbm->setSpeckleWindowSize(0);
    sbm->setUniquenessRatio(0);
    sbm->setTextureThreshold(507);
    sbm->setMinDisparity(-39);
    sbm->setPreFilterCap(61);
    sbm->setPreFilterSize(5);
    //sbm->compute(imgL,imgR, disp);


    normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);

    imshow("left", imgL);
    imshow("right", imgR);
    imshow("disp", disp8);

    cv::waitKey(0);

}



int main(){
    calib_img();
}
