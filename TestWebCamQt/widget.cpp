#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>

#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QTimer>
#include <cstdio>
#include <iostream>

using namespace cv;
using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    cap = VideoCapture(0);

    int frameWidth = 320;
    int frameHeight = 240;

    cap.set(CV_CAP_PROP_FRAME_WIDTH,frameWidth);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,frameHeight);

    if(!cap.isOpened())  // check if we succeeded
    {
        cerr<<"Error openning the default camera"<<endl;
    }

    if( !face_cascade.load( "../TestWebCamQt/fist.xml" ) )
    {
        cerr<<"Error loading haarcascade"<<endl;
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePicture()));
    timer->start(16);
}


Widget::~Widget()
{
    delete ui;
    delete webCam_;
}

void Widget::updatePicture()
    {
            Mat frame,frame_gray;
            std::vector<Rect> fist;
            // Get frame
            cap >> frame;
            // Mirror effect
            cv::flip(frame,frame,1);
            // Convert to gray
            cv::cvtColor(frame,frame_gray,COLOR_BGR2GRAY);

            //-- Detect fist
            face_cascade.detectMultiScale( frame_gray, fist, 1.1, 4, 0|CV_HAAR_SCALE_IMAGE, Size(60, 60) );
            if (fist.size()>0)
            {
                // Draw green rectangle
                for (int i=0;i<(int)fist.size();i++)
                    rectangle(frame,fist[i],Scalar(0,255,0),2);
            }


            cvtColor(frame, frame_gray,CV_BGR2RGB);
            QImage image1= QImage((uchar*) frame_gray.data, frame_gray.cols, frame_gray.rows, frame_gray.step, QImage::Format_RGB888);

            //show Qimage using QLabel
            ui->CamLabel_->setPixmap(QPixmap::fromImage(image1));
            ui->CamLabel_->show();
    }
