//
// Created by lucky.mz on 01.04.2018.
// c style


#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv/highgui.h>
#include <opencv2/imgproc.hpp>

int helloWorld() {
    // задаём высоту и ширину картинки
    int height = 620;
    int width = 440;
    // задаём точку для вывода текста
    CvPoint pt = cvPoint(height / 4, width / 2);
    // Создаёи 8-битную, 3-канальную картинку
    IplImage *hw = cvCreateImage(cvSize(height, width), 8, 3);
    // заливаем картинку чёрным цветом
    cvSet(hw, cvScalar(0, 0, 0));
    // инициализация шрифта
    CvFont font;
    cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 1.0, 1.0, 0, 1, CV_AA);
    // используя шрифт выводим на картинку текст
    cvPutText(hw, "OpenCV Step By Step", pt, &font, CV_RGB(150, 0, 150));
    // создаём окошко
    cvNamedWindow("Hello World", 0);
    // показываем картинку в созданном окне
    cvShowImage("Hello World", hw);
    // ждём нажатия клавиши
    cvWaitKey(0);
    // освобождаем ресурсы
    cvReleaseImage(&hw);
    cvDestroyWindow("Hello World");
}





IplImage* frame =0;

int video(int argc, char* argv[]) {
    // имя файла задаётся первым параметром
    char* filename = /**argc == 2 ? argv[1] :*/ const_cast<char *>
    ("/Users/lucky.mz/Documents/movies/shortAction.mp4");

    printf("[i] file: %s\n", filename);

    // окно для отображения картинки
    cvNamedWindow("original",CV_WINDOW_AUTOSIZE);

    // получаем информацию о видео-файле
    CvCapture* capture = cvCreateFileCapture( filename );

    while (1){
        // получаем следующий кадр
        frame = cvQueryFrame( capture );
        if( !frame ) {
            break;
        }

        // здесь можно вставить
        // процедуру обработки

        // показываем кадр
        cvShowImage( "original", frame );

        char c = cvWaitKey(33);
        if (c == 27) { // если нажата ESC - выходим
            break;
        }
    }

    // освобождаем ресурсы
    cvReleaseCapture( &capture );
    // удаляем окно
    cvDestroyWindow("original");
    return 0;
}




int cameraCapchure(int argc, char* argv[]) {
    // получаем любую подключённую камеру
    CvCapture* capture = cvCreateCameraCapture(CV_CAP_ANY); //cvCaptureFromCAM( 0 );
    assert( capture );

    //cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 640);//1280);
    //cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 480);//960);

    // узнаем ширину и высоту кадра
    double width = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
    double height = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
    printf("[i] %.0f x %.0f\n", width, height );

    IplImage* frame=0;

    cvNamedWindow("capture", CV_WINDOW_AUTOSIZE);

    printf("[i] press Enter for capture image and Esc for quit!\n\n");

    int counter=0;
    char filename[512];

    while(true){
        // получаем кадр
        frame = cvQueryFrame( capture );

        // показываем
        cvShowImage("capture", frame);

        char c = cvWaitKey(33);
        if (c == 27) { // нажата ESC
            break;
        }
        else if(c == 13) { // Enter
            // сохраняем кадр в файл
            sprintf(filename, "Image%d.jpg", counter);
            printf("[i] capture... %s\n", filename);
            cvSaveImage(filename, frame);
            counter++;
        }
    }
    // освобождаем ресурсы
    cvReleaseCapture( &capture );
    cvDestroyWindow("capture");
    return 0;
}


IplImage* image = 0;
IplImage* src = 0;

int imgLoad(int argc, char* argv[]){
    // имя картинки задаётся первым параметром
    char *filename = /**argc == 2 ? argv[1] :*/ const_cast<char *>
    ("/Users/lucky.mz/Documents/GitHub/RSE_lirs/sample.jpg");
    // получаем картинку
    image = cvLoadImage( filename,1);
    // клонируем картинку
    src = cvCloneImage(image);

    printf("[i] image: %s\n",  filename);
    assert( src != 0 );

    // окно для отображения картинки
    cvNamedWindow("original",CV_WINDOW_AUTOSIZE);

    // показываем картинку
    cvShowImage("original",image);

    // выводим в консоль информацию о картинке
    printf( "[i] channels:  %d\n",        image->nChannels );
    printf( "[i] pixel depth: %d bits\n",   image->depth );
    printf( "[i] width:       %d pixels\n", image->width );
    printf( "[i] height:      %d pixels\n", image->height );
    printf( "[i] image size:  %d bytes\n",  image->imageSize );
    printf( "[i] width step:  %d bytes\n",  image->widthStep );

    // ждём нажатия клавиши
    cvWaitKey(0);

    // освобождаем ресурсы
    cvReleaseImage(& image);
    cvReleaseImage(&src);
    // удаляем окно
    cvDestroyWindow("original");
    return 0;
}