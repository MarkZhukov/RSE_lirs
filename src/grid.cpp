//
// Created by lucky.mz on 28.04.2018.
//

#include <opencv/cv.h>
#include <opencv2/imgproc.hpp>

using namespace cv;


///cv::Mat_<uchar> img2 = img; // Ссылка на img
///img2(10,20) = 0; // Доступ к строке 10 и столбцу 20

void printGrideOnImage(){
    Mat img;
    // Отобразить на изображении белую пунктирную сетку
    for( int i = 0; i < img.rows; i++ ) {
        for (int j = 0; j < img.cols; j++) {
            if ((i % 20 == 10 && j % 2 == 1) ||
                (j % 50 == 25 && i % 2 == 1)) {
                ///if 8 bit uchar 1 channel
                //img.at<uchar>(i,j)= 255;
                ///else
                img.at<Vec3b>(i, j)[0] = 255;
                img.at<Vec3b>(i, j)[1] = 255;
                img.at<Vec3b>(i, j)[2] = 255;

            }
        }
    }

}

void changrColor(){
    Mat img;
    ///if grin -> red
    for( int i = 0; i < img.rows; i++ )
        for( int j = 0; j < img.cols; j++ )
            if ( img.at<Vec3b>(i,j)[0] < img.at<Vec3b>(i,j)[1] - 10 &&
                 img.at<Vec3b>(i,j)[2] < img.at<Vec3b>(i,j)[1] - 10 &&
                 img.at<Vec3b>(i,j)[1] > 64 )
            {
                img.at<Vec3b>(i,j)[0]= 0;
                img.at<Vec3b>(i,j)[1]= 0;
                img.at<Vec3b>(i,j)[2]= 255;
            }
}
void upLight() {
    Mat img;
    Mat img2;
    img.copyTo( img2 );
    img2 = img2 * 2; // Увеличение яркости в 2 раза
}

void region(){
    Rect r( 100, 50, 200, 150 ); // Создание региона
    Mat img;
    Mat img2;
    // Копирование региона в отдельное изображение
    img( r ).copyTo( img2 );
    img2 += CV_RGB(0,0,255); // Добавляем синего к изображению

    // Изменение части изображения
    img( r ) *= 0.5; // Понижение яркости
}
